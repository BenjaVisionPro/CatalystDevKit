// ============================================================================
// Catalyst Foundation — Base Factory for Model Assets (Editor)
// ----------------------------------------------------------------------------
// - Creates the UObject (invoked by UAssetDefinition).
// - Hidden from Add(+) and Content Browser; AssetDefinition owns placement.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CFModelAssetFactory.generated.h"

class UCFModelAsset;

UCLASS(Abstract)
class CATALYSTFOUNDATIONEDITOR_API UCFModelAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCFModelAssetFactory();

	// ----- UFactory -----
	// Factory remains usable, but invisible in Add(+).
	virtual bool ShouldShowInNewMenu() const override { return false; }

	// With AssetDefinitions, menu categories are unused; return 0 and avoid legacy headers.
	virtual uint32 GetMenuCategories() const override { return 0u; }

	virtual FText   GetDisplayName() const override;
	virtual FText   GetToolTip() const override;
	virtual UClass* ResolveSupportedClass() override;

	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

protected:
	/** Subclass must return the asset class it creates (must derive from UCFModelAsset). */
	virtual UClass* GetAssetClass() const PURE_VIRTUAL(UCFModelAssetFactory::GetAssetClass, return nullptr;);

	/** Label for palettes or internal creation. */
	virtual FText GetAssetMenuName() const PURE_VIRTUAL(UCFModelAssetFactory::GetAssetMenuName, return FText::FromString(TEXT("Model Asset")););

	/** Optional defaults. */
	virtual FString GetDefaultAssetName() const { return TEXT("Model"); }
	virtual void    InitializeNewAsset(UObject* NewAsset) const {}

private:
	bool ValidateSupportedClass(UClass* InClass) const;
};