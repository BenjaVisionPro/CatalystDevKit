/**
 * @file CFAbstractModelService.cpp
 * @brief Runtime owner for a plugin's live model snapshot (implementation).
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#include "Services/CFAbstractModelService.h"
#include "Model/CFModelAsset.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "ProfilingDebugging/CpuProfilerTrace.h" // TRACE_CPUPROFILER_EVENT_SCOPE
#include "Log/CFLog.h"

void UCFAbstractModelService::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CF_INFO(TEXT("Initialize()"));
	Seed  = GetSeedModelAsset();
	State = ECFModelServiceState::Loading;

	if (Seed.IsNull())
	{
		EmitError(ECFModelErrorCode::MissingSeed,
			TEXT("Seed model path is null. Cannot begin async load."),
			/*Context*/TEXT(""));
		State = ECFModelServiceState::Error;
		return;
	}

	StartLoadInternal();
}

void UCFAbstractModelService::Deinitialize()
{
	CF_INFO(TEXT("Deinitialize()"));

	// Prevent any follow-up refresh from launching during teardown.
	bRefreshPending.Store(false);
	bLoadInFlight.Store(false);

	// Release any in-flight async load.
	if (LoadHandle.IsValid())
	{
		LoadHandle.Reset();
	}

	{
		FWriteScopeLock Lock(ModelLock);
		Model = nullptr;
	}

	State = ECFModelServiceState::Uninitialized;
	Super::Deinitialize();
}

void UCFAbstractModelService::StartLoadInternal()
{
	if (bLoadInFlight.Exchange(true))
	{
		// Already loading; schedule a follow-up.
		bRefreshPending.Store(true);
		return;
	}

	// Fresh load begins.
	State = ECFModelServiceState::Loading;
	bRefreshPending.Store(false); // this load supersedes any prior request
	BeginAsyncLoad();
}

void UCFAbstractModelService::BeginAsyncLoad()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(CF_BeginAsyncLoad);

	if (Seed.IsNull())
	{
		EmitError(ECFModelErrorCode::MissingSeed,
			TEXT("BeginAsyncLoad() called with null Seed."),
			/*Context*/TEXT(""));
		State = ECFModelServiceState::Error;
		bLoadInFlight.Store(false);
		return;
	}

	FStreamableManager& SM = UAssetManager::GetStreamableManager();
	const FSoftObjectPath& Path = Seed.ToSoftObjectPath();

	FCFLogScopeTimer Scope(TEXT("SeedAsyncLoad"), /*ThresholdMs*/ 250.0);

	LoadHandle = SM.RequestAsyncLoad(
		Path,
		FStreamableDelegate::CreateUObject(this, &UCFAbstractModelService::OnSeedLoaded),
		FStreamableManager::AsyncLoadHighPriority
	);

	if (!LoadHandle.IsValid())
	{
		EmitError(ECFModelErrorCode::AsyncLoadFailed,
			FString::Printf(TEXT("Failed to start async load for seed: %s"), *Seed.ToString()),
			Seed.ToString());
		State = ECFModelServiceState::Error;
		bLoadInFlight.Store(false);
		return;
	}

	CF_INFO(TEXT("Async load started: %s"), *Seed.ToString());
}

void UCFAbstractModelService::OnSeedLoaded()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(CF_OnSeedLoaded);
	FCFLogScopeTimer Scope(TEXT("OnSeedLoaded->InstantiateApplyValidate"), /*ThresholdMs*/ 100.0);

	UCFModelAsset* SeedAsset = Seed.Get();
	if (!SeedAsset)
	{
		EmitError(ECFModelErrorCode::AsyncLoadFailed,
			FString::Printf(TEXT("Async load completed but seed is null: %s"), *Seed.ToString()),
			Seed.ToString());
		State = ECFModelServiceState::Error;
		bLoadInFlight.Store(false);
		MaybeRunPendingRefresh();
		return;
	}

	// Duplicate into a transient runtime instance.
	UCFModelAsset* Instance = nullptr;
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CF_DuplicateSeed);
		Instance = DuplicateObject<UCFModelAsset>(SeedAsset, this);
	}
	if (!Instance)
	{
		EmitError(ECFModelErrorCode::DuplicateFailed,
			TEXT("Failed to duplicate seed asset for live instance."),
			Seed.ToString());
		State = ECFModelServiceState::Error;
		bLoadInFlight.Store(false);
		MaybeRunPendingRefresh();
		return;
	}

	// Best-effort dev override from Saved/<Plugin>/Model.json (non-fatal).
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CF_ApplyDevJson);
		if (!TryApplyDevJson(Instance))
		{
			CF_WARN(TEXT("Dev JSON override failed; continuing with seed defaults."));
		}
	}

	// Optional validation hook.
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CF_ValidateModel);
		FString ValidationError;
		if (!ValidateModel(Instance, ValidationError))
		{
			const FString Msg = ValidationError.IsEmpty()
				? TEXT("Model validation failed.")
				: ValidationError;

			EmitError(ECFModelErrorCode::Unknown, Msg, Seed.ToString());
			State = ECFModelServiceState::Error;
			bLoadInFlight.Store(false);
			MaybeRunPendingRefresh();
			return;
		}
	}

	// Commit live instance.
	{
		FWriteScopeLock Lock(ModelLock);
		Model = Instance;
	}

	const bool bWasReady = bHasEverBeenReady;
	bHasEverBeenReady = true;

	State = ECFModelServiceState::Ready;

	if (!bWasReady)
	{
		CF_INFO(TEXT("Model READY (initial). Broadcasting OnModelReady."));
		OnModelReady.Broadcast(Model);
	}
	else
	{
		CF_INFO(TEXT("Model RELOADED (swap). Broadcasting OnModelReloaded + OnModelUpdated."));
		OnModelReloaded.Broadcast(Model);
		OnModelUpdated.Broadcast();
	}

	bLoadInFlight.Store(false);
	MaybeRunPendingRefresh();
}

void UCFAbstractModelService::MaybeRunPendingRefresh()
{
	// If a refresh was requested while this load was in-flight, run exactly one follow-up.
	if (bRefreshPending.Exchange(false))
	{
		CF_INFO(TEXT("Running coalesced follow-up refresh."));
		StartLoadInternal();
	}
}

bool UCFAbstractModelService::TryApplyDevJson(UCFModelAsset* Instance)
{
	if (!Instance)
	{
		EmitError(ECFModelErrorCode::JsonApplyFailed,
			TEXT("TryApplyDevJson called with null Instance."),
			/*Context*/TEXT(""));
		return false;
	}

	FCFLogScopeTimer Scope(TEXT("ApplyDevJSON"), /*ThresholdMs*/ 50.0);

	FString Error;
	if (!Instance->TryLoadFromDiskJson(Error))
	{
		// Treat "file not found" as non-fatal; still emit error for visibility if we got one.
		if (!Error.IsEmpty())
		{
			EmitError(ECFModelErrorCode::JsonApplyFailed, Error, Instance->GetSavedJsonFile());
		}
		return false;
	}

	CF_INFO(TEXT("Dev JSON applied successfully."));
	return true;
}

bool UCFAbstractModelService::ValidateModel(UCFModelAsset* /*Instance*/, FString& /*OutError*/) const
{
	// Default: no-op (valid). Subclasses can override to enforce invariants.
	return true;
}

const UCFModelAsset* UCFAbstractModelService::Get() const
{
	FReadScopeLock Lock(ModelLock);
	return Model;
}

UCFModelAsset* UCFAbstractModelService::GetMutable() // typo? keep original name:
{
	FWriteScopeLock Lock(ModelLock);
	return Model;
}

float UCFAbstractModelService::GetLoadProgress() const
{
	if (State == ECFModelServiceState::Ready)
	{
		return 1.0f;
	}
	if (State != ECFModelServiceState::Loading || !LoadHandle.IsValid())
	{
		return 0.0f;
	}
	return LoadHandle->GetProgress(); // 0..1 while loading
}

void UCFAbstractModelService::RefreshModel(const FString& Reason)
{
	CF_INFO(TEXT("RefreshModel(%s)"), *Reason);
	if (Seed.IsNull())
	{
		EmitError(ECFModelErrorCode::MissingSeed,
			TEXT("Refresh requested but Seed is null."),
			/*Context*/TEXT(""));
		State = ECFModelServiceState::Error;
		return;
	}

	StartLoadInternal();

	// If we were already Ready and no load actually starts (coalesced),
	// callers may still want an "updated" signal for local mutations.
	if (State == ECFModelServiceState::Ready && !bLoadInFlight.Load())
	{
		OnModelUpdated.Broadcast();
	}
}

void UCFAbstractModelService::EmitError(ECFModelErrorCode Code, FString Message, FString Context)
{
	// Stable, grep-able prefix for CI/logs
	CF_ERR(TEXT("[CFModelServiceError] Code=%d Msg=%s Ctx=%s"),
		(int32)Code, *Message, *Context);

	FCFModelError E;
	E.Code = Code;
	E.Message = MoveTemp(Message);
	E.Context = MoveTemp(Context);

	// New, typed payload first
	OnModelErrorEx.Broadcast(E);

	// Legacy string payload for existing listeners
	OnModelError.Broadcast(E.Message);
}
