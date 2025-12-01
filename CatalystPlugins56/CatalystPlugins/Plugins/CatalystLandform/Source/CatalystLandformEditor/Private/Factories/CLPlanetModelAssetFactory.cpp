// ============================================================================
// Catalyst Landform — Planet Model Asset Factory (Editor)
// ============================================================================

#include "Factories/CLPlanetModelAssetFactory.h"
#include "Model/CLPlanetModelAsset.h"
#include "Log/CFLog.h"

UCLPlanetModelAssetFactory::UCLPlanetModelAssetFactory()
{
	bCreateNew    = true;
	bEditAfterNew = true;

	SupportedClass = UCLPlanetModelAsset::StaticClass();

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
	// Respect InClass if it’s a subclass of UCLPlanetModelAsset, otherwise fall back.
	UClass* TargetClass = InClass ? InClass : UCLPlanetModelAsset::StaticClass();
	if (!TargetClass->IsChildOf(UCLPlanetModelAsset::StaticClass()))
	{
		TargetClass = UCLPlanetModelAsset::StaticClass();
	}

	UObject* NewAsset = NewObject<UCLPlanetModelAsset>(
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