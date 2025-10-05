// ============================================================================
// Catalyst Foundation — Base Factory for Model Assets (Editor)
// ----------------------------------------------------------------------------
// Purpose:
//   - Standardize “Add New → Catalyst → …” creation for model assets.
//   - Ensures supported asset classes derive from UCFModelAsset.
//   - Feature plugins subclass and implement GetAssetClass() + GetAssetMenuName().
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
	virtual bool    ShouldShowInNewMenu() const override { return true; }
	virtual uint32  GetMenuCategories() const override;      // “Catalyst” category bit
	virtual FText   GetDisplayName() const override;         // Menu text
	virtual FText   GetToolTip() const override;             // Tooltip
	virtual UClass* ResolveSupportedClass() override;        // UE signature (non-const)
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

	/** Subclass supplies the menu label. */
	virtual FText   GetAssetMenuName() const PURE_VIRTUAL(UCFModelAssetFactory::GetAssetMenuName, return FText::FromString(TEXT("Model Asset")););

	/** Optional defaults. */
	virtual FString GetDefaultAssetName() const { return TEXT("Model"); }
	virtual void    InitializeNewAsset(UObject* NewAsset) const {}

private:
	bool ValidateSupportedClass(UClass* InClass) const;
};