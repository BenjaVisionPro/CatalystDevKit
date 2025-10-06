// ============================================================================
// Implementation
// ============================================================================

#include "Factories/CEModelAssetFactory.h"
#include "Model/CEModelAsset.h"
#include "Log/CFLog.h"

UCEModelAssetFactory::UCEModelAssetFactory()
{
	bCreateNew    = true;
	bEditAfterNew = true;
	SupportedClass = UCEModelAsset::StaticClass();

	CF_INFO(TEXT("[%s] ctor; SupportedClass=%s"),
		*GetClass()->GetName(), *GetNameSafe(SupportedClass));
}

FText UCEModelAssetFactory::GetDisplayName() const
{
	// Shown only in diagnostic contexts, not in Add(+)
	static const FText Name = NSLOCTEXT(
		"CatalystEcosystemEditor",
		"CEModelAssetFactory_DisplayName",
		"Ecosystem");

	return Name;
}

UObject* UCEModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	UClass* TargetClass = InClass ? InClass : UCEModelAsset::StaticClass();

	UObject* NewAsset = NewObject<UCEModelAsset>(
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