#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "__PREFIX__AssetDefinition_Model.generated.h"

UCLASS()
class CATALYSTECOSYSTEMEDITOR_API U__PREFIX__AssetDefinition_Model : public UAssetDefinitionDefault
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