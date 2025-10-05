// ============================================
// Catalyst Foundation — Abstract Model Service
// Logging pass: CFLog macros + contextual messages
// ============================================

#include "Services/CFAbstractModelService.h"
#include "Model/CFModelAsset.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Foundation logging
#include "Log/CFLog.h"

void UCFAbstractModelService::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Tag logs with plugin/service context early.
	CF_INFO(TEXT("Initialize()"));

	Seed  = GetSeedModelAsset();
	State = ECFModelServiceState::Loading;

	if (Seed.IsNull())
	{
		const FString Msg = TEXT("Seed model path is null. Cannot begin async load.");
		CF_ERR(TEXT("%s"), *Msg);
		State = ECFModelServiceState::Error;
		OnModelError.Broadcast(Msg);
		return;
	}

	CF_INFO(TEXT("BeginAsyncLoad(): %s"), *Seed.ToString());
	BeginAsyncLoad();
}

void UCFAbstractModelService::Deinitialize()
{
	CF_INFO(TEXT("Deinitialize()"));

	// Release any in-flight async load.
	if (LoadHandle.IsValid())
	{
		CF_INFO(TEXT("Releasing async load handle"));
		LoadHandle.Reset();
	}

	{
		FWriteScopeLock Lock(ModelLock);
		Model = nullptr;
	}

	State = ECFModelServiceState::Uninitialized;

	Super::Deinitialize();
}

void UCFAbstractModelService::BeginAsyncLoad()
{
	// Defensive guard (Initialize also checks)
	if (Seed.IsNull())
	{
		const FString Msg = TEXT("BeginAsyncLoad() called with null Seed.");
		CF_ERR(TEXT("%s"), *Msg);
		State = ECFModelServiceState::Error;
		OnModelError.Broadcast(Msg);
		return;
	}

	FStreamableManager& SM = UAssetManager::GetStreamableManager();
	const FSoftObjectPath& Path = Seed.ToSoftObjectPath();

	// Timer: warn if loading takes > 250ms (tweak as needed)
	FCFLogScopeTimer Scope(TEXT("SeedAsyncLoad"), /*ThresholdMs*/ 250.0);

	LoadHandle = SM.RequestAsyncLoad(
		Path,
		FStreamableDelegate::CreateUObject(this, &UCFAbstractModelService::OnSeedLoaded),
		FStreamableManager::AsyncLoadHighPriority
	);

	if (!LoadHandle.IsValid())
	{
		const FString Msg = FString::Printf(TEXT("Failed to start async load for seed: %s"), *Seed.ToString());
		CF_ERR(TEXT("%s"), *Msg);
		State = ECFModelServiceState::Error;
		OnModelError.Broadcast(Msg);
		return;
	}

	CF_INFO(TEXT("Async load started: %s"), *Seed.ToString());
}

void UCFAbstractModelService::OnSeedLoaded()
{
	// Timer around post-load work (dup + JSON)
	FCFLogScopeTimer Scope(TEXT("OnSeedLoaded->InstantiateAndApplyJSON"), /*ThresholdMs*/ 100.0);

	UCFModelAsset* SeedAsset = Seed.Get();
	if (!SeedAsset)
	{
		const FString Msg = FString::Printf(TEXT("Async load completed but seed is null: %s"), *Seed.ToString());
		CF_ERR(TEXT("%s"), *Msg);
		State = ECFModelServiceState::Error;
		OnModelError.Broadcast(Msg);
		return;
	}

	CF_INFO(TEXT("Seed loaded: %s (duplicating)"), *Seed.ToString());

	// Duplicate into a transient runtime instance.
	UCFModelAsset* Instance = DuplicateObject<UCFModelAsset>(SeedAsset, this);
	if (!Instance)
	{
		const FString Msg = TEXT("Failed to duplicate seed asset for live instance.");
		CF_ERR(TEXT("%s"), *Msg);
		State = ECFModelServiceState::Error;
		OnModelError.Broadcast(Msg);
		return;
	}

	// Best-effort dev override from Saved/<Plugin>/Model.json.
	if (!TryApplyDevJson(Instance))
	{
		// Non-fatal; continue with seed defaults.
		CF_WARN(TEXT("Dev JSON override failed; continuing with seed defaults."));
	}

	{
		FWriteScopeLock Lock(ModelLock);
		Model = Instance;
	}

	State = ECFModelServiceState::Ready;
	CF_INFO(TEXT("Model READY (live duplicate in memory). Broadcasting OnModelReady."));
	OnModelReady.Broadcast(Model);
}

bool UCFAbstractModelService::TryApplyDevJson(UCFModelAsset* Instance)
{
	if (!Instance)
	{
		CF_ERR(TEXT("TryApplyDevJson called with null Instance."));
		return false;
	}

	// Timer: warn if JSON apply takes > 50ms
	FCFLogScopeTimer Scope(TEXT("ApplyDevJSON"), /*ThresholdMs*/ 50.0);

	FString Error;
	if (!Instance->TryLoadFromDiskJson(Error))
	{
		CF_ERR(TEXT("Dev JSON apply failed: %s"), *Error);
		OnModelError.Broadcast(Error);
		return false;
	}

	CF_INFO(TEXT("Dev JSON applied successfully."));
	return true;
}

const UCFModelAsset* UCFAbstractModelService::Get() const
{
	FReadScopeLock Lock(ModelLock);
	return Model;
}

UCFModelAsset* UCFAbstractModelService::GetMutable()
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