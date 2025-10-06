#include "Factories/CEModelAssetFactory.h"
#include "Model/CEModelAsset.h"

UClass* UCEModelAssetFactory::GetAssetClass() const
{
	return UCEModelAsset::StaticClass();
}

FText UCEModelAssetFactory::GetAssetMenuName() const
{
	return NSLOCTEXT("CatalystEcosystemEditor", "CEModelFactory_Menu", "Ecosystem");
}

void UCEModelAssetFactory::InitializeNewAsset(UObject* NewAsset) const
{
	if (UCEModelAsset* Asset = Cast<UCEModelAsset>(NewAsset))
	{
		// Optionally initialize defaults here.
	}
}