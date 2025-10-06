#include "AssetDefinitions/CFAssetDefinition_Model.h"
#include "Model/CFModelAsset.h"
#include "Containers/ArrayView.h"
#include "Misc/AssetCategoryPath.h"

TSoftClassPtr<UObject> UCFAssetDefinition_Model::GetAssetClass() const
{
    return TSoftClassPtr<UObject>(UCFModelAsset::StaticClass());
}

TConstArrayView<FAssetCategoryPath> UCFAssetDefinition_Model::GetAssetCategories() const
{
    // UE5.6 requires FText-based constructors. No TEXT("...") here.
    static const FAssetCategoryPath Cats[] = {
        FAssetCategoryPath(
            NSLOCTEXT("CatalystFoundationEditor", "CF_CatalystCat", "Catalyst"))
    };
    return MakeArrayView(Cats);
}