#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Schema/FBVCMADescription.h"
#include "UBVCValidationEngine.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FBVCValidationIssue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString FieldPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MessageCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Message;
};

UCLASS()
class CATALYSTCONNECT_API UBVCValidationEngine : public UObject
{
    GENERATED_BODY()

public:
    // Validate a single field against its Magritte description
    UFUNCTION(BlueprintCallable, Category="BVC|Validation")
    bool ValidateField(const FBVCMADescription& Description,
                       FName Field,
                       const FString& Value,
                       UPARAM(ref) TArray<FBVCValidationIssue>& OutIssues) const;

    // Validate all fields in an object (placeholder for now)
    UFUNCTION(BlueprintCallable, Category="BVC|Validation")
    bool ValidateObject(const FBVCMADescription& Description,
                        UPARAM(ref) TArray<FBVCValidationIssue>& OutIssues) const;
};
