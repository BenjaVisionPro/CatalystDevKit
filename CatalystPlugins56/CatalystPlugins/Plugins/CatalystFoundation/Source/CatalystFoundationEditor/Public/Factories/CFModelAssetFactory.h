#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h" // Reimport pipeline
#include "CFModelAssetFactory.generated.h"

class UCFModelAsset;

UCLASS(Abstract)
class CATALYSTFOUNDATIONEDITOR_API UCFModelAssetFactory 
	: public UFactory
	, public FReimportHandler
{
	GENERATED_BODY()

public:
	UCFModelAssetFactory();

	// ----- UFactory -----
	virtual bool   ShouldShowInNewMenu() const override { return false; }
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
	virtual FText   GetAssetMenuName() const PURE_VIRTUAL(UCFModelAssetFactory::GetAssetMenuName, return FText::FromString(TEXT("Model Asset")););

	virtual FString GetDefaultAssetName() const { return TEXT("Model"); }
	virtual void    InitializeNewAsset(UObject* NewAsset) const {}

private:
	bool ValidateSupportedClass(UClass* InClass) const;

	// ----- FReimportHandler -----
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
};