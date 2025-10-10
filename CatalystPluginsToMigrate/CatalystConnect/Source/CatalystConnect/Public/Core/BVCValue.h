#pragma once
#include "CoreMinimal.h"
#include "BVCValue.generated.h"

UENUM()
enum class EBVCValueType : uint8
{
    None, Bool, Int32, Int64, Float, Double, String, Name, Guid, ByteArray, Array, Map, EnumString
};

USTRUCT()
struct CATALYSTCONNECT_API FBVCValue
{
    GENERATED_BODY()

    UPROPERTY() EBVCValueType Type = EBVCValueType::None;

    UPROPERTY() bool   Bool  = false;
    UPROPERTY() int32  Int32 = 0;
    UPROPERTY() int64  Int64 = 0;
    UPROPERTY() float  Float = 0.f;
    UPROPERTY() double Double = 0.0;
    UPROPERTY() FString String;
    UPROPERTY() FName   Name;
    UPROPERTY() FGuid   Guid;
    UPROPERTY() TArray<uint8> ByteArray;

    // Recursive members: NOT UPROPERTY, use shared pointers to avoid incomplete-type issues.
    TArray<TSharedPtr<FBVCValue>> Array;
    TMap<FName, TSharedPtr<FBVCValue>> Map;

    // convenience makers
    static FBVCValue MakeString(FString In)
    {
        FBVCValue V; V.Type = EBVCValueType::String; V.String = MoveTemp(In); return V;
    }
};
