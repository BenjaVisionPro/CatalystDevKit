/**
 * @file CFAbstractModelService.h
 * @brief Abstract base type used as a shared foundation for Catalyst data objects.
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

/** Service lifecycle state (global-scope UENUM). */
UENUM(BlueprintType)
enum class ECFModelServiceState : uint8
{
    Uninitialized UMETA(DisplayName="Uninitialized"),
    Loading       UMETA(DisplayName="Loading"),
    Ready         UMETA(DisplayName="Ready"),
    Error         UMETA(DisplayName="Error")
};

/**
 * Runtime owner of a plugin model (Foundation base).
 *
 * - Loads the seed asset asynchronously (soft reference only).
 * - Duplicates the seed into a transient, runtime-owned instance.
 * - Optionally applies a dev JSON override (Saved/<Plugin>/Model.json).
 * - Exposes readiness/error/update delegates.
 * - Thread-safe getters via FRWLock.
 *
 * Subclasses must implement:
 *   GetPluginName()       -> "CatalystEcosystem", etc.
 *   GetSeedModelAsset()   -> Soft path to the generated seed asset (.uasset)
 */
UCLASS(Abstract)
class CATALYSTFOUNDATION_API UCFAbstractModelService : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // ----- Subsystem lifecycle -----
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ----- Accessors (thread-safe) -----
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

    // ----- Plugin identity (required) -----
    virtual FName GetPluginName() const PURE_VIRTUAL(UCFAbstractModelService::GetPluginName, return NAME_None;);
    virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const PURE_VIRTUAL(UCFAbstractModelService::GetSeedModelAsset, return nullptr;);

    // ----- Delegates -----
    /** Fired once the live model is ready. */
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelReady, UCFModelAsset* /*Live*/);
    /** Fired when async load or JSON application fails. */
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelError, const FString& /*Message*/);
    /** Fired when the live model is mutated/replaced after Ready (opt-in by callers). */
    DECLARE_MULTICAST_DELEGATE(FOnModelUpdated);

    FOnModelReady   OnModelReady;
    FOnModelError   OnModelError;
    FOnModelUpdated OnModelUpdated;

protected:
    // Kick off async load of the seed; called from Initialize.
    void BeginAsyncLoad();

    // Bound to Streamable completion.
    void OnSeedLoaded();

    // Applies dev JSON override; returns false on failure (non-fatal).
    bool TryApplyDevJson(UCFModelAsset* Instance);

protected:
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
};