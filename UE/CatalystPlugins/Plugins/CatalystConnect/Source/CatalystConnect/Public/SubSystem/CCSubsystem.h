// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Connection/BVCConnectionConfig.h"
#include "CCSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCCSubsystem, Log, All);

class UBVCConnection;

/**
 * UCCSubsystem
 *
 * Thin factory/locator for BVC connections.
 * - Does NOT store or track created connections.
 * - Callers own the returned UBVCConnection objects.
 */
UCLASS()
class CATALYSTCONNECT_API UCCSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Convenience accessor from any world context. */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection", meta=(WorldContext="WorldContextObject"))
    static UCCSubsystem* Get(const UObject* WorldContextObject);

    /** Create a new connection UObject, initialize it, and return it. Caller owns the reference. */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    UBVCConnection* CreateConnection(const FBVCConnectionConfig& Config);

private:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
};
