#pragma once
#include "CoreMinimal.h"
#include "FBVCMAValidatorSpec.h"
#include "FBVCMAAttribute.generated.h"

UENUM(BlueprintType) enum class EBVCMAKind : uint8 { Scalar, ToOne, ToMany, Enum, Map };
UENUM(BlueprintType) enum class EBVCMAScalarType : uint8 { None, Bool, Int32, Int64, Float32, Float64, String, Name, Guid, ByteArray, DateTime };

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCMAAttribute
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBVCMAKind Kind = EBVCMAKind::Scalar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBVCMAScalarType ScalarType = EBVCMAScalarType::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bNullable = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double EpsilonAbs = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double EpsilonRel = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> EnumSymbols;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Label;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Help;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Category;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DefaultValueJson;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FBVCMAValidatorSpec> Validators;
};
