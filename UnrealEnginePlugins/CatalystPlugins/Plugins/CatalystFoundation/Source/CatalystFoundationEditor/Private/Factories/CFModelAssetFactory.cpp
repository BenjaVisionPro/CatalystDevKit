// ============================================================================
// Catalyst Foundation — Base Factory for Model Assets (Editor) — impl
// ============================================================================

#include "Factories/CFModelAssetFactory.h"

// Removed legacy dependency on CFEditorModule/log.
// #include "CFEditorModule.h"

#include "Model/CFModelAsset.h"
#include "AssetTypeCategories.h"   // OK in .cpp
#include "Modules/ModuleManager.h"
#include "Log/CFLog.h"             // << use CF_INFO/CF_WARN/CF_ERR/CF_CAT_LOG

UCFModelAssetFactory::UCFModelAssetFactory()
{
	bCreateNew     = true;
	bEditAfterNew  = true;
	SupportedClass = nullptr; // resolve at create-time via ResolveSupportedClass()

	CF_INFO(TEXT("[%s] ctor: bCreateNew=%d bEditAfterNew=%d"),
		*GetClass()->GetName(), (int32)bCreateNew, (int32)bEditAfterNew);
}

uint32 UCFModelAssetFactory::GetMenuCategories() const
{
	// Irrelevant now that Add(+) is AssetDefinition-driven; must still return something valid.
	return (uint32)EAssetTypeCategories::Misc;
}

FText UCFModelAssetFactory::GetDisplayName() const
{
	const FText Name = GetAssetMenuName();
	CF_INFO(TEXT("[%s] GetDisplayName -> \"%s\""),
		*GetClass()->GetName(), *Name.ToString());
	return Name;
}

FText UCFModelAssetFactory::GetToolTip() const
{
	static const FText Tip = NSLOCTEXT("CatalystFoundationEditor", "CFModelAssetFactory_Tooltip",
		"Create a new Catalyst model asset.");
	return Tip;
}

UClass* UCFModelAssetFactory::ResolveSupportedClass()
{
	UClass* Target = GetAssetClass();

	CF_INFO(TEXT("[%s] ResolveSupportedClass (raw) -> %s"),
		*GetClass()->GetName(), Target ? *Target->GetName() : TEXT("<null>"));

	if (!ValidateSupportedClass(Target))
	{
		Target = UCFModelAsset::StaticClass();
		CF_WARN(TEXT("[%s] ResolveSupportedClass fallback -> UCFModelAsset"),
			*GetClass()->GetName());
	}
	return Target;
}

bool UCFModelAssetFactory::ValidateSupportedClass(UClass* InClass) const
{
	if (!InClass)
	{
		CF_ERR(TEXT("[%s] GetAssetClass() returned null."), *GetClass()->GetName());
		return false;
	}
	if (!InClass->IsChildOf(UCFModelAsset::StaticClass()))
	{
		CF_ERR(TEXT("[%s] %s does not derive from UCFModelAsset."),
			*GetClass()->GetName(), *InClass->GetName());
		return false;
	}
	return true;
}

UObject* UCFModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	CF_INFO(TEXT("[%s] FactoryCreateNew: InClass=%s Parent=%s Name=%s Flags=0x%08x"),
		*GetClass()->GetName(),
		InClass ? *InClass->GetName() : TEXT("<null>"),
		InParent ? *InParent->GetName() : TEXT("<null>"),
		*Name.ToString(),
		(uint32)Flags);

	UClass* TargetClass = InClass ? InClass : ResolveSupportedClass();
	if (!ValidateSupportedClass(TargetClass))
	{
		CF_ERR(TEXT("[%s] Aborting create; invalid TargetClass."), *GetClass()->GetName());
		return nullptr;
	}

	// Create the concrete asset instance.
	UObject* NewAsset = NewObject<UObject>(InParent, TargetClass, Name, Flags | RF_Public | RF_Standalone);
	if (!NewAsset)
	{
		CF_ERR(TEXT("[%s] Failed to create asset %s of class %s"),
			*GetClass()->GetName(), *Name.ToString(), *TargetClass->GetName());
		return nullptr;
	}

	CF_INFO(TEXT("[%s] Created asset object: %s (%s)"),
		*GetClass()->GetName(), *NewAsset->GetName(), *TargetClass->GetName());

	InitializeNewAsset(NewAsset);
	return NewAsset;
}