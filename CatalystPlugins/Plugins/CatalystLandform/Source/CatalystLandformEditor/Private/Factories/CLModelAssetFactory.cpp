// ============================================================================
// Implementation
// ============================================================================

#include "Factories/CLModelAssetFactory.h"
#include "Model/CLModelAsset.h"
#include "Log/CFLog.h"

UCLModelAssetFactory::UCLModelAssetFactory()
{
	bCreateNew    = true;
	bEditAfterNew = true;
	SupportedClass = UCLModelAsset::StaticClass();

	CF_INFO(TEXT("[%s] ctor; SupportedClass=%s"),
		*GetClass()->GetName(), *GetNameSafe(SupportedClass));
}

FText UCLModelAssetFactory::GetDisplayName() const
{
	// Shown only in diagnostic contexts, not in Add(+)
	static const FText Name = NSLOCTEXT(
		"CatalystLandformEditor",
		"CLModelAssetFactory_DisplayName",
		"Landform");

	return Name;
}

UObject* UCLModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	UClass* TargetClass = InClass ? InClass : UCLModelAsset::StaticClass();

	UObject* NewAsset = NewObject<UCLModelAsset>(
		InParent,
		TargetClass,
		Name,
		Flags | RF_Public | RF_Standalone);

	CF_INFO(TEXT("[%s] FactoryCreateNew -> %s (%s)"),
		*GetClass()->GetName(),
		*GetNameSafe(NewAsset),
		*GetNameSafe(TargetClass));

	return NewAsset;
}