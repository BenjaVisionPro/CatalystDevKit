// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CFSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCFSubsystem, Log, All);

/**
 * UCFSubsystem
 *
 * Thin factory/locator for BVC connections.
 * - Does NOT store or track created connections.
 */
UCLASS()
class CATALYSTFOUNDATION_API UCFSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Convenience accessor from any world context. */
    UFUNCTION(BlueprintCallable, Category="BVC|Ecosystem", meta=(WorldContext="WorldContextObject"))
    static UCFSubsystem* Get(const UObject* WorldContextObject);

private:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
};
