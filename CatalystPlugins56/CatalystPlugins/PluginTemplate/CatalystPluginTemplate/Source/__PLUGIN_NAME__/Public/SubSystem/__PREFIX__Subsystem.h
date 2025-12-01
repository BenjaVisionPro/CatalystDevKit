// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "__PREFIX__Subsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCESubsystem, Log, All);

/**
 * U__PREFIX__Subsystem
 *
 * Thin factory/locator for BVC connections.
 * - Does NOT store or track created connections.
 * - Callers own the returned UBVCEonnection objects.
 */
UCLASS()
class __PLUGIN_API__ U__PREFIX__Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Convenience accessor from any world context. */
    UFUNCTION(BlueprintCallable, Category="__PREFIX__", meta=(WorldContext="WorldContextObject"))
    static U__PREFIX__Subsystem* Get(const UObject* WorldContextObject);

private:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
};
