#pragma once

#include "CoreMinimal.h"
#include "Factories/CFModelAssetFactory.h"
#include "CEModelAssetFactory.generated.h"

/**
 * Factory for Ecosystem model assets.
 * Appears under: Add New → Catalyst → Ecosystems → Ecosystem
 */
UCLASS()
class CATALYSTECOSYSTEMEDITOR_API UCEModelAssetFactory : public UCFModelAssetFactory
{
	GENERATED_BODY()

protected:
	// UCFModelAssetFactory
	virtual UClass* GetAssetClass() const override;
	virtual FText   GetAssetMenuName() const override;
	virtual FString GetDefaultAssetName() const override { return TEXT("Ecosystem"); }
	virtual void    InitializeNewAsset(UObject* NewAsset) const override;

	/** Optional: for menu grouping (not overriding any UFactory API). */
	TArray<FText> GetSubMenus() const
	{
		return { NSLOCTEXT("CatalystEcosystemEditor", "CE_Submenu_Ecosystems", "Ecosystems") };
	}
};