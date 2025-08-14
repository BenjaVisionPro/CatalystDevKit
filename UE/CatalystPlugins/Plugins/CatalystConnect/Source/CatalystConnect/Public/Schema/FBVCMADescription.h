#pragma once
#include "CoreMinimal.h"
#include "FBVCMAAttribute.h"
#include "FBVCMADescription.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCMADescription
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGuid ClassId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Version = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Hash;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Identifier; // id slot
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FBVCMAAttribute> Attributes;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> MethodNames;
};
