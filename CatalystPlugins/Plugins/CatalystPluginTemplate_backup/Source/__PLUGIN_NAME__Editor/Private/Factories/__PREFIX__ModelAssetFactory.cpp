// ============================================================================
// Implementation
// ============================================================================

#include "Factories/__PREFIX__ModelAssetFactory.h"
#include "Model/__PREFIX__ModelAsset.h"
#include "Log/CFLog.h"

U__PREFIX__ModelAssetFactory::U__PREFIX__ModelAssetFactory()
{
	bCreateNew    = true;
	bEditAfterNew = true;
	SupportedClass = U__PREFIX__ModelAsset::StaticClass();

	CF_INFO(TEXT("[%s] ctor; SupportedClass=%s"),
		*GetClass()->GetName(), *GetNameSafe(SupportedClass));
}

FText U__PREFIX__ModelAssetFactory::GetDisplayName() const
{
	// Shown only in diagnostic contexts, not in Add(+)
	static const FText Name = NSLOCTEXT(
		"__PLUGIN_NAME__Editor",
		"__PREFIX__ModelAssetFactory_DisplayName",
		"Ecosystem");

	return Name;
}

UObject* U__PREFIX__ModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	UClass* TargetClass = InClass ? InClass : U__PREFIX__ModelAsset::StaticClass();

	UObject* NewAsset = NewObject<U__PREFIX__ModelAsset>(
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