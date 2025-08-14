#pragma once
#include "CoreMinimal.h"
#include "FBVCMADescription.h"
#include "FBVCMADescriptionContainer.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCMADescriptionContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGuid CatalogId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Version = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Hash;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FBVCMADescription> Descriptions;
};
