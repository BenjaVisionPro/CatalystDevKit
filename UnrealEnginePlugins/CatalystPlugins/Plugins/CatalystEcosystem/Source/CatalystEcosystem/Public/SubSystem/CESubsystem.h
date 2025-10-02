// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CESubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCESubsystem, Log, All);

/**
 * UCESubsystem
 *
 * Thin factory/locator for BVC connections.
 * - Does NOT store or track created connections.
 * - Callers own the returned UBVCEonnection objects.
 */
UCLASS()
class CATALYSTECOSYSTEM_API UCESubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Convenience accessor from any world context. */
    UFUNCTION(BlueprintCallable, Category="BVC|Ecosystem", meta=(WorldContext="WorldContextObject"))
    static UCESubsystem* Get(const UObject* WorldContextObject);

private:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
};
