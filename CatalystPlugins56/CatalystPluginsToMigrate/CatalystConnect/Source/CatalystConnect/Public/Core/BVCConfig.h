#pragma once
#include "CoreMinimal.h"
#include "BVCConfig.generated.h"
UENUM(BlueprintType) enum class EBVCQoS : uint8 { High, Medium, Low };
UENUM(BlueprintType) enum class EBVCValidationSetMode : uint8 { Off, Deferred, Eager };
USTRUCT(BlueprintType)
struct FBVCConfig {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ProjectPrefix;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bDeliverOnGameThread = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBVCValidationSetMode OnSetField = EBVCValidationSetMode::Deferred;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bClientValidationEnabled = true;
};
