/**
 * @file CFAbstractModelService.h
 * @brief Runtime owner for a plugin's live model snapshot:
 *        async-loads the seed asset, duplicates to a transient instance,
 *        applies dev JSON (if present), then exposes a thread-safe live model.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CFAbstractModelService.generated.h"

class UCFModelAsset;
struct FStreamableHandle;

/** Service lifecycle state. */
UENUM(BlueprintType)
enum class ECFModelServiceState : uint8
{
	Uninitialized UMETA(DisplayName="Uninitialized"),
	Loading       UMETA(DisplayName="Loading"),
	Ready         UMETA(DisplayName="Ready"),
	Error         UMETA(DisplayName="Error")
};

/** Lightweight, structured error info for CI/tools/editors (non-breaking). */
UENUM(BlueprintType)
enum class ECFModelErrorCode : uint8
{
	None,
	MissingSeed,
	AsyncLoadFailed,
	DuplicateFailed,
	JsonParseFailed,
	JsonApplyFailed,
	Unknown
};

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFModelError
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="CF|ModelService")
	ECFModelErrorCode Code = ECFModelErrorCode::None;

	UPROPERTY(VisibleAnywhere, Category="CF|ModelService")
	FString Message;

	/** Optional context: asset path, file path, etc. */
	UPROPERTY(VisibleAnywhere, Category="CF|ModelService")
	FString Context;
};

/**
 * @brief Foundation runtime service that owns the live model for a plugin.
 *
 * Responsibilities:
 * - Asynchronously loads the seed asset by soft reference.
 * - Duplicates the seed into a transient, runtime-owned instance.
 * - Optionally applies a developer JSON override (non-fatal on failure).
 * - Exposes readiness/error/update delegates.
 * - Provides a debounced Refresh() that coalesces concurrent requests.
 * - Thread-safe getters guarded by FRWLock.
 *
 * Subclasses must implement:
 * - GetPluginName()         → "CatalystEcosystem", etc.
 * - GetSeedModelAsset()     → Soft path to the generated seed asset (.uasset)
 */
UCLASS(Abstract)
class CATALYSTFOUNDATION_API UCFAbstractModelService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// --- Subsystem lifecycle ---
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// --- Accessors (thread-safe) ---
	/** Read-only access to the live model (nullptr until Ready). */
	UFUNCTION(BlueprintCallable, Category="CF|ModelService")
	const UCFModelAsset* Get() const;

	/** Mutable access to the live model (nullptr until Ready). */
	UFUNCTION(BlueprintCallable, Category="CF|ModelService")
	UCFModelAsset* GetMutable();

	/** Current service state. */
	UFUNCTION(BlueprintCallable, Category="CF|ModelService")
	ECFModelServiceState GetState() const { return State; }

	/** 0..1 while async-loading; 1 when Ready; 0 on Error/Uninitialized. */
	UFUNCTION(BlueprintCallable, Category="CF|ModelService")
	float GetLoadProgress() const;

	/**
	 * @brief Request a model refresh (debounced).
	 * If a load is in-flight, sets a pending flag and runs one follow-up load
	 * immediately after the current completes. Multiple calls coalesce.
	 */
	UFUNCTION(BlueprintCallable, Category="CF|ModelService")
	void RefreshModel(const FString& Reason = TEXT(""));

	// --- Plugin identity (required) ---
	virtual FName GetPluginName() const PURE_VIRTUAL(UCFAbstractModelService::GetPluginName, return NAME_None;);
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const PURE_VIRTUAL(UCFAbstractModelService::GetSeedModelAsset, return nullptr;);

	// --- Delegates ---
	/** Fired once on the first successful load. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelReady, UCFModelAsset* /*Live*/);
	/** Fired on subsequent successful loads when the live instance is swapped. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelReloaded, UCFModelAsset* /*Live*/);
	/** Fired when async load or JSON application fails (legacy, string message). */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelError, const FString& /*Message*/);
	/** New: typed error payload for tools/CI. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelErrorEx, const FCFModelError& /*Error*/);
	/** Fired when the live model is mutated/replaced after Ready (refresh or local mutation). */
	DECLARE_MULTICAST_DELEGATE(FOnModelUpdated);

	FOnModelReady    OnModelReady;
	FOnModelReloaded OnModelReloaded;
	FOnModelError    OnModelError;    // legacy
	FOnModelErrorEx  OnModelErrorEx;  // structured
	FOnModelUpdated  OnModelUpdated;

protected:
	// --- Load/refresh internals ---
	void BeginAsyncLoad();                               // initial load at Initialize()
	void OnSeedLoaded();                                 // streamable completion
	bool TryApplyDevJson(UCFModelAsset* Instance);       // best-effort, non-fatal
	bool ValidateModel(UCFModelAsset* Instance, FString& OutError) const; // optional

	/** Structured error helper; emits both typed and legacy delegates. */
	void EmitError(ECFModelErrorCode Code, FString Message, FString Context = FString());

private:
	/** Starts a new load (used by initial load and any follow-up refresh). */
	void StartLoadInternal();

	/** Called after OnSeedLoaded finishes; runs any pending refresh. */
	void MaybeRunPendingRefresh();

private:
	// Transient, runtime-owned duplicate of the seed.
	UPROPERTY(Transient)
	UCFModelAsset* Model = nullptr;

	// Soft reference to the seed (.uasset). Provided by subclass.
	UPROPERTY(Transient)
	TSoftObjectPtr<UCFModelAsset> Seed;

	// Handle to cancel/track async load on deinit.
	TSharedPtr<FStreamableHandle> LoadHandle;

	// Thread-safety for Get()/GetMutable().
	mutable FRWLock ModelLock;

	// State (editor/runtime-friendly).
	UPROPERTY(Transient)
	ECFModelServiceState State = ECFModelServiceState::Uninitialized;

	// Debounce/Coalescing flags.
	TAtomic<bool> bLoadInFlight{false};
	TAtomic<bool> bRefreshPending{false};

	// Distinguish first Ready from subsequent reloads.
	UPROPERTY(Transient)
	bool bHasEverBeenReady = false;
};