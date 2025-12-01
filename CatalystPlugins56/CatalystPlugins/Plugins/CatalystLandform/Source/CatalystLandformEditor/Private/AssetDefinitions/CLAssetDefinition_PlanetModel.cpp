#include "AssetDefinitions/CLAssetDefinition_PlanetModel.h"
#include "Model/CLPlanetModelAsset.h"
#include "Toolkits/CLModelEditorToolkit.h"   // per-plugin wrapper
#include "Log/CFLog.h"

// Extra diagnostics
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "CLAssetDefinition_PlanetModel"

FText UCLAssetDefinition_PlanetModel::GetAssetDisplayName() const
{
	return LOCTEXT("CLPlanet_DisplayName", "Planet");
}

FLinearColor UCLAssetDefinition_PlanetModel::GetAssetColor() const
{
	return FLinearColor(0.30f, 0.60f, 0.90f);
}

TSoftClassPtr<UObject> UCLAssetDefinition_PlanetModel::GetAssetClass() const
{
	CF_INFO(TEXT("[CLAssetDefinition_PlanetModel] GetAssetClass -> CLPlanetModelAsset"));
	return UCLPlanetModelAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UCLAssetDefinition_PlanetModel::GetAssetCategories() const
{
	static const FText Root = LOCTEXT("CatalystTopCat", "Catalyst");
	static const FText Mid  = LOCTEXT("CatalystSubCat_Landform", "Landform");

	static const FAssetCategoryPath RootToMid(Root, Mid);
	static const FAssetCategoryPath Paths[] = { RootToMid };

	CF_INFO(TEXT("[CLAssetDefinition_PlanetModel] GetAssetCategories -> [Catalyst/Landform]"));
	return Paths;
}

EAssetCommandResult UCLAssetDefinition_PlanetModel::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	CF_WARN(TEXT("[CLAssetDefinition_PlanetModel] >>> OpenAssets CALLED"));
	CF_INFO(TEXT("  OpenMethod=%d  ToolkitHost=%s"),
		static_cast<int32>(OpenArgs.OpenMethod),
		OpenArgs.ToolkitHost.IsValid() ? TEXT("VALID") : TEXT("NULL"));

#if WITH_EDITOR
	if (GEditor)
	{
		CF_INFO(TEXT("  GEditor OK, CurrentWorld=%s"),
			*GetNameSafe(GEditor->GetEditorWorldContext().World()));
	}
#endif

	const EToolkitMode::Type Mode =
		(OpenArgs.ToolkitHost.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone);

	const TArray<UCLPlanetModelAsset*> Assets = OpenArgs.LoadObjects<UCLPlanetModelAsset>();
	CF_INFO(TEXT("[CLAssetDefinition_PlanetModel] Loaded %d object(s)."), Assets.Num());

	if (Assets.Num() == 0)
	{
		CF_WARN(TEXT("[CLAssetDefinition_PlanetModel] No assets resolved by LoadObjects<UCLPlanetModelAsset>()."));
		return EAssetCommandResult::Unhandled;
	}

	for (UCLPlanetModelAsset* Asset : Assets)
	{
		if (!Asset)
		{
			CF_WARN(TEXT("[CLAssetDefinition_PlanetModel] -> Null asset, skipping."));
			continue;
		}

		CF_INFO(TEXT("[CLAssetDefinition_PlanetModel] -> Launch CLModelEditorToolkit for '%s' (Mode=%s)"),
			*Asset->GetName(),
			Mode == EToolkitMode::WorldCentric ? TEXT("WorldCentric") : TEXT("Standalone"));

		TSharedRef<FCLModelEditorToolkit> Editor = MakeShared<FCLModelEditorToolkit>();
		Editor->InitModelEditor(Asset, Mode, OpenArgs.ToolkitHost);

#if WITH_EDITOR
		bool bHasEditor = false;
		if (GEditor)
		{
			if (UAssetEditorSubsystem* AES = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			{
				bHasEditor = (AES->FindEditorForAsset(Asset, /*bFocusIfOpen=*/false) != nullptr);
			}
		}
		CF_INFO(TEXT("[CLAssetDefinition_PlanetModel] -> RegisteredWithAssetEditorSubsystem=%s"),
			bHasEditor ? TEXT("YES") : TEXT("NO"));
#endif
	}

	CF_WARN(TEXT("[CLAssetDefinition_PlanetModel] <<< OpenAssets DONE"));
	return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE