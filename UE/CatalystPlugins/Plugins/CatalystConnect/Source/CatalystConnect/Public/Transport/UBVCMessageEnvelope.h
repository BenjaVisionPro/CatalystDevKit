#pragma once
#include "CoreMinimal.h"
#include "UBVCMessageEnvelope.generated.h"
USTRUCT() struct FBVCMessageEnvelope {
    GENERATED_BODY()
    UPROPERTY() FString Type; UPROPERTY() FString Encoding; UPROPERTY() FString Compression;
    UPROPERTY() FString MessageId; UPROPERTY() FString TimestampUtc; UPROPERTY() FString Nonce;
};
