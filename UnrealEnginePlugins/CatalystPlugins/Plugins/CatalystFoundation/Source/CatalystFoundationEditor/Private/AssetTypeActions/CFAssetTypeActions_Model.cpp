#include "AssetTypeActions/CFAssetTypeActions_Model.h"

#include "CFEditorModule.h"                 // FCFEditorAssetCategory + LogCFEditor
#include "Model/CFModelAsset.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "Editor.h"
#include "AssetRegistry/AssetData.h"

FCFAssetTypeActions_Model::FCFAssetTypeActions_Model(FText InDisplayName, FColor InTypeColor)
	: DisplayName(MoveTemp(InDisplayName))
	, TypeColor(InTypeColor)
{
}

FText FCFAssetTypeActions_Model::GetName() const
{
	return DisplayName;
}

FColor FCFAssetTypeActions_Model::GetTypeColor() const
{
	return TypeColor;
}

uint32 FCFAssetTypeActions_Model::GetCategories()
{
	return static_cast<uint32>(FCFEditorAssetCategory::Get());
}

UClass* FCFAssetTypeActions_Model::GetSupportedClass() const
{
	UClass* Cls = GetAssetClass();
	if (!Cls)
	{
		UE_LOG(LogCFEditor, Error, TEXT("AssetTypeActions: GetAssetClass() returned null"));
		return UCFModelAsset::StaticClass(); // safe fallback
	}
	if (!Cls->IsChildOf(UCFModelAsset::StaticClass()))
	{
		UE_LOG(LogCFEditor, Error,
		       TEXT("AssetTypeActions: %s does not derive from UCFModelAsset"), *Cls->GetName());
		return UCFModelAsset::StaticClass();
	}
	return Cls;
}

void FCFAssetTypeActions_Model::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (UObject* Obj : InObjects)
	{
		if (UCFModelAsset* Model = Cast<UCFModelAsset>(Obj))
		{
			OpenModelEditor(Model, Mode, EditWithinLevelEditor);
		}
	}
}

FText FCFAssetTypeActions_Model::GetAssetDescription(const FAssetData& AssetData) const
{
	// Prefer a description without loading the asset (future: tag summary on cook/generate).
	// Fallback: load if resident and asset supplies a summary.
	if (const UCFModelAsset* Asset = Cast<UCFModelAsset>(AssetData.FastGetAsset(/*bLoadIfNotInMemory*/ false)))
	{
		const FString Summary = Asset->GetSummaryText();
		if (!Summary.IsEmpty())
		{
			return FText::FromString(Summary);
		}
	}

	return FText::FromString(TEXT("Catalyst data model asset."));
}