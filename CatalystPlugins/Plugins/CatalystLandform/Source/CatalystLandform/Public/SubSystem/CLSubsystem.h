// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CLSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCESubsystem, Log, All);

/**
 * UCLSubsystem
 *
 * Thin factory/locator for BVC connections.
 * - Does NOT store or track created connections.
 * - Callers own the returned UBVCEonnection objects.
 */
UCLASS()
class CATALYSTLANDFORM_API UCLSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Convenience accessor from any world context. */
    UFUNCTION(BlueprintCallable, Category="CL", meta=(WorldContext="WorldContextObject"))
    static UCLSubsystem* Get(const UObject* WorldContextObject);

private:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
};
