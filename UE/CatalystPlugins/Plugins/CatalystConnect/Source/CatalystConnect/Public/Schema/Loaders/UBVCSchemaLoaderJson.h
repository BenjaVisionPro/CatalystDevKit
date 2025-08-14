#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Schema/FBVCMADescriptionContainer.h"
#include "UBVCSchemaLoaderJson.generated.h"

/**
 * Loads a Magritte-like schema catalog from a JSON string into FBVCMADescriptionContainer.
 * v1: strict field names; enums as strings (matching existing enum names).
 */
UCLASS()
class CATALYSTCONNECT_API UBVCSchemaLoaderJson : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="BVC|Schema")
    bool LoadFromJsonString(const FString& Json, FBVCMADescriptionContainer& OutContainer) const;
};
