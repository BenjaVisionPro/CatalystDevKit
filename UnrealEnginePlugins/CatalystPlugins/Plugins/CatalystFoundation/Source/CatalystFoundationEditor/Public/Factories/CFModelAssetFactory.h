// ============================================================================
// Catalyst Foundation — Base Factory for Model Assets (Editor)
// ----------------------------------------------------------------------------
// Post-AssetDefinition notes:
// - Factory still creates the UObject.
// - Add(+) menu placement is handled by UAssetDefinition*.
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
	// Keep hidden from Add(+) — AssetDefinitions control UI.
	virtual bool    ShouldShowInNewMenu() const override { return false; }

	// Declare only; implement in .cpp (avoids pulling engine headers into public API).
	virtual uint32  GetMenuCategories() const override;

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

	/** Label used in non-Add(+) contexts (palettes, etc.). */
	virtual FText   GetAssetMenuName() const PURE_VIRTUAL(UCFModelAssetFactory::GetAssetMenuName, return FText::FromString(TEXT("Model Asset")););

	/** Optional defaults. */
	virtual FString GetDefaultAssetName() const { return TEXT("Model"); }
	virtual void    InitializeNewAsset(UObject* NewAsset) const {}

private:
	bool ValidateSupportedClass(UClass* InClass) const;
};