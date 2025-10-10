// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ====================================

#pragma once
#include "CoreMinimal.h"
#include "BVCConnectionConfig.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCConnectionConfig
{
    GENERATED_BODY()

    /** Unique ID for this session (used as key in the subsystem). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Connection")
    FName SessionName;

    /** Display label (optional, UI only). If empty, defaults to SessionName. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Connection")
    FString DisplayLabel;

    /** Endpoint URL (ws://, wss://, etc.). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Connection")
    FString Url;

    /** Max reassembled message size in bytes. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Connection")
    int32 MaxMessageBytes = 16 * 1024 * 1024;

    /** Fragment timeout for reassembly, seconds. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Connection")
    double FragmentTimeoutSeconds = 10.0;
};
