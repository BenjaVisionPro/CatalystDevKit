#include "AssetDefinitions/__PREFIX__AssetDefinition_Model.h"
#include "Model/__PREFIX__ModelAsset.h"
#include "Toolkits/CFModelEditorToolkit.h"
#include "Log/CFLog.h"

// Extra diagnostics
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "__PREFIX__AssetDefinition_Model"

FText U__PREFIX__AssetDefinition_Model::GetAssetDisplayName() const
{
    return LOCTEXT("CE_Ecosystem_DisplayName", "Ecosystem");
}

FLinearColor U__PREFIX__AssetDefinition_Model::GetAssetColor() const
{
    return FLinearColor(0.30f, 0.60f, 0.90f);
}

TSoftClassPtr<UObject> U__PREFIX__AssetDefinition_Model::GetAssetClass() const
{
    CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] GetAssetClass -> __PREFIX__ModelAsset"));
    return U__PREFIX__ModelAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> U__PREFIX__AssetDefinition_Model::GetAssetCategories() const
{
    static const FText Root = LOCTEXT("CatalystTopCat", "Catalyst");
    static const FText Mid  = LOCTEXT("CatalystSubCat_Ecosystems", "Ecosystems");

    static const FAssetCategoryPath RootToMid(Root, Mid);
    static const FAssetCategoryPath Paths[] = { RootToMid };

    CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] GetAssetCategories -> [Catalyst/Ecosystems]"));
    return Paths;
}

EAssetCommandResult U__PREFIX__AssetDefinition_Model::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    CF_WARN(TEXT("[__PREFIX__AssetDefinition_Model] >>> OpenAssets CALLED"));
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

    // World-centric if a host is provided; otherwise standalone.
    const EToolkitMode::Type Mode =
        (OpenArgs.ToolkitHost.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone);

    // Load the assets we’re opening (typed).
    const TArray<U__PREFIX__ModelAsset*> Assets = OpenArgs.LoadObjects<U__PREFIX__ModelAsset>();
    CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] Loaded %d object(s)."), Assets.Num());

    if (Assets.Num() == 0)
    {
        CF_WARN(TEXT("[__PREFIX__AssetDefinition_Model] No assets resolved by LoadObjects<U__PREFIX__ModelAsset>()."));
        return EAssetCommandResult::Unhandled;
    }

    for (U__PREFIX__ModelAsset* Asset : Assets)
    {
        if (!Asset)
        {
            CF_WARN(TEXT("[__PREFIX__AssetDefinition_Model] -> Null asset, skipping."));
            continue;
        }

        CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] -> Launch CFModelEditorToolkit for '%s' (Mode=%s)"),
            *Asset->GetName(),
            Mode == EToolkitMode::WorldCentric ? TEXT("WorldCentric") : TEXT("Standalone"));

        // Create our toolkit and init it
        TSharedRef<FCFModelEditorToolkit> Editor = MakeShared<FCFModelEditorToolkit>();
        Editor->InitModelEditor(Asset, Mode, OpenArgs.ToolkitHost);

        // Diagnostic: confirm the editor subsystem now knows about an editor for this asset
        bool bHasEditor = false;
#if WITH_EDITOR
        if (GEditor)
        {
            if (UAssetEditorSubsystem* AES = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
            {
                bHasEditor = (AES->FindEditorForAsset(Asset, /*bFocusIfOpen=*/false) != nullptr);
            }
        }
#endif
        CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] -> RegisteredWithAssetEditorSubsystem=%s"),
            bHasEditor ? TEXT("YES") : TEXT("NO"));
    }

    CF_WARN(TEXT("[__PREFIX__AssetDefinition_Model] <<< OpenAssets DONE"));
    return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE