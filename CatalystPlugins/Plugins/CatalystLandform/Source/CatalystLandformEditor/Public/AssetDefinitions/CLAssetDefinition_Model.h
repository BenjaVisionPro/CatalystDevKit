#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "CLAssetDefinition_Model.generated.h"

UCLASS()
class CATALYSTLANDFORMEDITOR_API UCLAssetDefinition_Model : public UAssetDefinitionDefault
{
    GENERATED_BODY()
public:
    virtual FText GetAssetDisplayName() const override;
    virtual FLinearColor GetAssetColor() const override;
    virtual TSoftClassPtr<UObject> GetAssetClass() const override;
    virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

    // UE5.6: custom editor launcher for this asset type
    virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};