#include "AssetDefinitions/CFAssetDefinition_Model.h"
#include "Model/CFModelAsset.h"

TSoftClassPtr<UObject> UCFAssetDefinition_Model::GetAssetClass() const
{
    return TSoftClassPtr<UObject>(UCFModelAsset::StaticClass());
}

TConstArrayView<FAssetCategoryPath> UCFAssetDefinition_Model::GetAssetCategories() const
{
    // Top-level: Catalyst
    static const FText Cat     = NSLOCTEXT("CatalystFoundationEditor", "CatalystTopCat", "Catalyst");
    static const FAssetCategoryPath Paths[] = {
        FAssetCategoryPath(Cat)
    };
    return Paths;
}