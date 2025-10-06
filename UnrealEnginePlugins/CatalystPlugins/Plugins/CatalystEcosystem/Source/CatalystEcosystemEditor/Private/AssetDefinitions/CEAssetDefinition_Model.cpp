// CEAssetDefinition_Model.cpp
#include "AssetDefinitions/CEAssetDefinition_Model.h"
#include "Model/CEModelAsset.h"
#include "Log/CFLog.h"

#define LOCTEXT_NAMESPACE "CEAssetDefinition_Model"

FText UCEAssetDefinition_Model::GetAssetDisplayName() const
{
    // No "Model" suffix per convention
    return LOCTEXT("CE_Ecosystem_DisplayName", "Ecosystem");
}

FLinearColor UCEAssetDefinition_Model::GetAssetColor() const
{
    return FLinearColor(0.30f, 0.60f, 0.90f);
}

TSoftClassPtr<UObject> UCEAssetDefinition_Model::GetAssetClass() const
{
    CF_INFO(TEXT("[CEAssetDefinition_Model] GetAssetClass -> CEModelAsset"));
    return UCEModelAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UCEAssetDefinition_Model::GetAssetCategories() const
{
    // Catalyst → Ecosystems → (asset item named "Ecosystem")
    static const FText Root = LOCTEXT("CatalystTopCat", "Catalyst");
    static const FText Mid  = LOCTEXT("CatalystSubCat_Ecosystems", "Ecosystems");

    static const FAssetCategoryPath RootToMid(Root, Mid);
    static const FAssetCategoryPath Paths[] = { RootToMid };

    CF_INFO(TEXT("[CEAssetDefinition_Model] GetAssetCategories -> [Catalyst/Ecosystems]"));
    return Paths;
}

#undef LOCTEXT_NAMESPACE