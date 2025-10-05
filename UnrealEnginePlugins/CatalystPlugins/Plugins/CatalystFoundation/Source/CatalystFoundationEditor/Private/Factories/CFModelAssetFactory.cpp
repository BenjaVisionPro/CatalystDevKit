#include "Factories/CFModelAssetFactory.h"

#include "CFEditorModule.h"          // FCFEditorAssetCategory::Get(), LogCFEditor
#include "Model/CFModelAsset.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

UCFModelAssetFactory::UCFModelAssetFactory()
{
	bCreateNew     = true;
	bEditAfterNew  = true;
	SupportedClass = nullptr; // we resolve dynamically via ResolveSupportedClass()
}

uint32 UCFModelAssetFactory::GetMenuCategories() const
{
	return static_cast<uint32>(FCFEditorAssetCategory::Get());
}

FText UCFModelAssetFactory::GetDisplayName() const
{
	return GetAssetMenuName();
}

FText UCFModelAssetFactory::GetToolTip() const
{
	return NSLOCTEXT("CatalystFoundationEditor", "CFModelAssetFactory_Tooltip",
		"Create a new Catalyst model asset.");
}

UClass* UCFModelAssetFactory::ResolveSupportedClass()
{
	UClass* Target = GetAssetClass();
	if (!ValidateSupportedClass(Target))
	{
		Target = UCFModelAsset::StaticClass();
	}
	return Target;
}

bool UCFModelAssetFactory::ValidateSupportedClass(UClass* InClass) const
{
	if (!InClass)
	{
		UE_LOG(LogCFEditor, Error, TEXT("CFModelAssetFactory: GetAssetClass() returned null."));
		return false;
	}
	if (!InClass->IsChildOf(UCFModelAsset::StaticClass()))
	{
		UE_LOG(LogCFEditor, Error,
			TEXT("CFModelAssetFactory: %s does not derive from UCFModelAsset."),
			*InClass->GetName());
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
		return nullptr;
	}

	UObject* NewAsset = NewObject<UObject>(InParent, TargetClass, Name, Flags | RF_Public | RF_Standalone);
	if (!NewAsset)
	{
		UE_LOG(LogCFEditor, Error,
			TEXT("CFModelAssetFactory: Failed to create asset %s of class %s"),
			*Name.ToString(), *TargetClass->GetName());
		return nullptr;
	}

	InitializeNewAsset(NewAsset);
	return NewAsset;
}