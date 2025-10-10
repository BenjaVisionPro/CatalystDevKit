#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UBVCSubscriptionHandle.h"
#include "UBVCRemoteObjectSpace.generated.h"

/**
 * UBVCRemoteObjectSpace
 * Root coordinator for remote model subscriptions and dispatch.
 * (Lightweight for v1: just manages subscription bookkeeping.)
 */
UCLASS(BlueprintType)
class CATALYSTCONNECT_API UBVCRemoteObjectSpace : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="BVC|ObjectSpace")
    FBVCSubscriptionHandle Subscribe(const TArray<FString>& Classes, FName Topic, bool bDeliverOnGameThread);

    UFUNCTION(BlueprintCallable, Category="BVC|ObjectSpace")
    void Unsubscribe(FBVCSubscriptionHandle Handle);

private:
    UPROPERTY()
    int64 LastSubId = 0;
};
