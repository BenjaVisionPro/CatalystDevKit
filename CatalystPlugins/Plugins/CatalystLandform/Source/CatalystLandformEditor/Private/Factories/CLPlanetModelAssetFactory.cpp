// ============================================================================
// Catalyst Landform — Planet Model Asset Factory (Editor)
// ============================================================================

#include "Factories/CLPlanetModelAssetFactory.h"
#include "Model/CLWorldAsset.h"
#include "Log/CFLog.h"

UCLPlanetModelAssetFactory::UCLPlanetModelAssetFactory()
{
	bCreateNew    = true;
	bEditAfterNew = true;

	SupportedClass = UCLWorldAsset::StaticClass();

	CF_INFO(TEXT("[%s] ctor; SupportedClass=%s"),
		*GetClass()->GetName(),
		*GetNameSafe(SupportedClass));
}

FText UCLPlanetModelAssetFactory::GetDisplayName() const
{
	// Mostly diagnostic; the real UX name is driven by UCLAssetDefinition_PlanetModel
	static const FText Name = NSLOCTEXT(
		"CatalystLandformEditor",
		"CLPlanetModelAssetFactory_DisplayName",
		"Planet");

	return Name;
}

UObject* UCLPlanetModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	// Respect InClass if it’s a subclass of UCLWorldAsset, otherwise fall back.
	UClass* TargetClass = InClass ? InClass : UCLWorldAsset::StaticClass();
	if (!TargetClass->IsChildOf(UCLWorldAsset::StaticClass()))
	{
		TargetClass = UCLWorldAsset::StaticClass();
	}

	UObject* NewAsset = NewObject<UCLWorldAsset>(
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