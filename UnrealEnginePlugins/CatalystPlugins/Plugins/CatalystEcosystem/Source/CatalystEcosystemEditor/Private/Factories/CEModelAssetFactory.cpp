// ============================================================================
// Catalyst Ecosystem — Model Asset Factory (Editor)
// ============================================================================

#include "Factories/CEModelAssetFactory.h"
#include "Model/CEModelAsset.h"
#include "Log/CFLog.h"

UCEModelAssetFactory::UCEModelAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCEModelAsset::StaticClass();

	CF_INFO(TEXT("[CEModelAssetFactory] ctor; SupportedClass=%s"),
		*GetNameSafe(SupportedClass));
}

FText UCEModelAssetFactory::GetDisplayName() const
{
	const FText Name = NSLOCTEXT("CatalystEcosystemEditor", "CEModelAssetFactory_DisplayName", "Ecosystem Model");
	CF_INFO(TEXT("[%s] GetDisplayName -> \"%s\""), *GetClass()->GetName(), *Name.ToString());
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
	return NewObject<UCEModelAsset>(
		InParent,
		InClass ? InClass : UCEModelAsset::StaticClass(),
		Name,
		Flags | RF_Public | RF_Standalone);
}