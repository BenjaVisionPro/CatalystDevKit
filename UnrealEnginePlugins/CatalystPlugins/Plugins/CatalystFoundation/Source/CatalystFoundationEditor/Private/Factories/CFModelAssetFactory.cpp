// ============================================================================
// Catalyst Foundation — Base Factory for Model Assets (Editor) — impl
// ============================================================================

#include "Factories/CFModelAssetFactory.h"
#include "Model/CFModelAsset.h"
#include "Log/CFLog.h"

UCFModelAssetFactory::UCFModelAssetFactory()
{
	bCreateNew     = true;
	bEditAfterNew  = true;
	SupportedClass = nullptr; // Resolved dynamically

	CF_INFO(TEXT("[%s] ctor: bCreateNew=%d bEditAfterNew=%d"),
		*GetClass()->GetName(), (int32)bCreateNew, (int32)bEditAfterNew);
}

FText UCFModelAssetFactory::GetDisplayName() const
{
	return GetAssetMenuName();
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
	if (!ValidateSupportedClass(Target))
	{
		Target = UCFModelAsset::StaticClass();
		CF_WARN(TEXT("[%s] Invalid or null asset class; falling back to UCFModelAsset"),
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
	UClass* TargetClass = InClass ? InClass : ResolveSupportedClass();
	if (!ValidateSupportedClass(TargetClass))
	{
		CF_ERR(TEXT("[%s] Aborting create; invalid TargetClass."), *GetClass()->GetName());
		return nullptr;
	}

	UObject* NewAsset = NewObject<UObject>(InParent, TargetClass, Name, Flags | RF_Public | RF_Standalone);
	if (!NewAsset)
	{
		CF_ERR(TEXT("[%s] Failed to create asset %s of class %s"),
			*GetClass()->GetName(), *Name.ToString(), *TargetClass->GetName());
		return nullptr;
	}

	InitializeNewAsset(NewAsset);
	return NewAsset;
}