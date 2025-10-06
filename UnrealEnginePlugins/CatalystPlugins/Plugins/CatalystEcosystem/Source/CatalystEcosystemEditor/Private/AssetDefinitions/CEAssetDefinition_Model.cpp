#include "AssetDefinitions/CEAssetDefinition_Model.h"
#include "Model/CEModelAsset.h"
#include "Containers/ArrayView.h"
#include "Misc/AssetCategoryPath.h"

TSoftClassPtr<UObject> UCEAssetDefinition_Model::GetAssetClass() const
{
    return TSoftClassPtr<UObject>(UCEModelAsset::StaticClass());
}

TConstArrayView<FAssetCategoryPath> UCEAssetDefinition_Model::GetAssetCategories() const
{
    // Explicit nested path via FText overload (two-arg ctor).
    static const FAssetCategoryPath Cats[] = {
        FAssetCategoryPath(
            NSLOCTEXT("CatalystFoundationEditor", "CF_CatalystCat", "Catalyst"),
            NSLOCTEXT("CatalystEcosystemEditor", "CE_EcosystemCat", "Ecosystem"))
    };
    return MakeArrayView(Cats);
}