#include "AssetDefinitions/__PREFIX__AssetDefinition_Model.h"
#include "Model/__PREFIX__ModelAsset.h"
#include "Toolkits/__PREFIX__ModelEditorToolkit.h"   // <-- per-plugin wrapper
#include "Log/CFLog.h"

// Extra diagnostics
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "__PREFIX__AssetDefinition_Model"

FText U__PREFIX__AssetDefinition_Model::GetAssetDisplayName() const
{
    return LOCTEXT("_PREFIX_____PLUGIN_DISPLAY_NAME___DisplayName", "__PLUGIN_DISPLAY_NAME__");
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
    static const FText Mid  = LOCTEXT("CatalystSubCat___PLUGIN_DISPLAY_NAME__", "__PLUGIN_DISPLAY_NAME__");

    static const FAssetCategoryPath RootToMid(Root, Mid);
    static const FAssetCategoryPath Paths[] = { RootToMid };

    CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] GetAssetCategories -> [Catalyst/__PLUGIN_DISPLAY_NAME__]"));
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

    const EToolkitMode::Type Mode =
        (OpenArgs.ToolkitHost.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone);

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

        CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] -> Launch __PREFIX__ModelEditorToolkit for '%s' (Mode=%s)"),
            *Asset->GetName(),
            Mode == EToolkitMode::WorldCentric ? TEXT("WorldCentric") : TEXT("Standalone"));

        // *** Use the per-plugin thin subclass (branding/extension seam) ***
        TSharedRef<F__PREFIX__ModelEditorToolkit> Editor = MakeShared<F__PREFIX__ModelEditorToolkit>();
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
        CF_INFO(TEXT("[__PREFIX__AssetDefinition_Model] -> RegisteredWithAssetEditorSubsystem=%s"),
            bHasEditor ? TEXT("YES") : TEXT("NO"));
#endif
    }

    CF_WARN(TEXT("[__PREFIX__AssetDefinition_Model] <<< OpenAssets DONE"));
    return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE