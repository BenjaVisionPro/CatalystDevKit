#pragma once
#include "CoreMinimal.h"
#include "UBVCSubscriptionHandle.generated.h"

USTRUCT(BlueprintType)
struct FBVCSubscriptionHandle {
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int64 SubId = 0;
};
