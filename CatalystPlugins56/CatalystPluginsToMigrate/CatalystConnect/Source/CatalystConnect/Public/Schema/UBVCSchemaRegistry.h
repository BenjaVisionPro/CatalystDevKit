#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FBVCMADescriptionContainer.h"
#include "UBVCSchemaRegistry.generated.h"

UCLASS(BlueprintType)
class CATALYSTCONNECT_API UBVCSchemaRegistry : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="BVC|Schema")
    void RegisterCatalog(const FBVCMADescriptionContainer& InContainer) { Catalog = InContainer; }

    UFUNCTION(BlueprintPure, Category="BVC|Schema")
    bool FindByName(FName ClassName, FBVCMADescription& OutDescription) const;

    UFUNCTION(BlueprintCallable, Category="BVC|Schema")
    void SetProjectPrefix(const FString& InPrefix) { ProjectPrefix = InPrefix; }

    UFUNCTION(BlueprintPure, Category="BVC|Schema")
    FString ResolveUObjectTypeName(const FString& ModelClassName) const
    {
        return FString::Printf(TEXT("U%s%s"), *ProjectPrefix, *ModelClassName);
    }

private:
    UPROPERTY() FBVCMADescriptionContainer Catalog;
    UPROPERTY() FString ProjectPrefix;
};
