#pragma once

#include "AssetDefinitionDefault.h"
#include "UObject/SoftObjectPtr.h"
#include "CFAssetDefinition_Model.generated.h"

class UCFModelAsset;

/**
 * Foundation base AssetDefinition for Catalyst "Model" assets.
 * - Places assets under top-level Add menu: "Catalyst"
 * - Centralizes display name / color (children may override)
 */
UCLASS(Abstract)
class CATALYSTFOUNDATIONEDITOR_API UCFAssetDefinition_Model : public UAssetDefinitionDefault
{
    GENERATED_BODY()
public:
    virtual TSoftClassPtr<UObject> GetAssetClass() const override;

    virtual FText        GetAssetDisplayName() const override
    {
        return NSLOCTEXT("CatalystFoundationEditor", "CF_Model_DisplayName", "Catalyst Model");
    }

    virtual FLinearColor GetAssetColor() const override
    {
        return FLinearColor(0.15f, 0.85f, 0.65f);
    }

    // Top-level Add menu category
    virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};