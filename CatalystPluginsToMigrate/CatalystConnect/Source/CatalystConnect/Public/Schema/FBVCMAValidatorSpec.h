#pragma once
#include "CoreMinimal.h"
#include "FBVCMAValidatorSpec.generated.h"

UENUM(BlueprintType)
enum class EBVCMAValidatorType : uint8
{
    Required, Length, Range, Regex, Enumeration, CrossField, UniqueInArray, CustomRef
};

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCMAValidatorSpec
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBVCMAValidatorType Type = EBVCMAValidatorType::Required;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ArgsJson;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString MessageCode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Message;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString WhenExpr;
};
