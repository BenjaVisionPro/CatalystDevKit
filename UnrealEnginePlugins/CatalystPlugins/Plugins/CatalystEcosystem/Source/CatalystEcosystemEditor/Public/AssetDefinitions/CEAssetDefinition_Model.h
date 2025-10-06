#pragma once

#include "AssetDefinitions/CFAssetDefinition_Model.h"
#include "CEAssetDefinition_Model.generated.h"

class UCEModelAsset;

/**
 * Ecosystem AssetDefinition
 * - Keeps placement under Catalyst, optionally as "Catalyst / Ecosystem"
 */
UCLASS()
class CATALYSTECOSYSTEMEDITOR_API UCEAssetDefinition_Model : public UCFAssetDefinition_Model
{
    GENERATED_BODY()
public:
    virtual TSoftClassPtr<UObject> GetAssetClass() const override;

    virtual FText GetAssetDisplayName() const override
    {
        return NSLOCTEXT("CatalystEcosystemEditor", "CE_Model_DisplayName", "Ecosystem");
    }

    // Nested menu path: Catalyst / Ecosystem
    virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};