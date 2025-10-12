#include "AssetDefinitions/CLAssetDefinition_Model.h"
#include "Model/CLModelAsset.h"
#include "Toolkits/CLModelEditorToolkit.h"   // <-- per-plugin wrapper
#include "Log/CFLog.h"

// Extra diagnostics
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "CLAssetDefinition_Model"

FText UCLAssetDefinition_Model::GetAssetDisplayName() const
{
    return LOCTEXT("_PREFIX___Landform_DisplayName", "Landform");
}

FLinearColor UCLAssetDefinition_Model::GetAssetColor() const
{
    return FLinearColor(0.30f, 0.60f, 0.90f);
}

TSoftClassPtr<UObject> UCLAssetDefinition_Model::GetAssetClass() const
{
    CF_INFO(TEXT("[CLAssetDefinition_Model] GetAssetClass -> CLModelAsset"));
    return UCLModelAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UCLAssetDefinition_Model::GetAssetCategories() const
{
    static const FText Root = LOCTEXT("CatalystTopCat", "Catalyst");
    static const FText Mid  = LOCTEXT("CatalystSubCat_Landform", "Landform");

    static const FAssetCategoryPath RootToMid(Root, Mid);
    static const FAssetCategoryPath Paths[] = { RootToMid };

    CF_INFO(TEXT("[CLAssetDefinition_Model] GetAssetCategories -> [Catalyst/Landform]"));
    return Paths;
}

EAssetCommandResult UCLAssetDefinition_Model::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    CF_WARN(TEXT("[CLAssetDefinition_Model] >>> OpenAssets CALLED"));
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

    const TArray<UCLModelAsset*> Assets = OpenArgs.LoadObjects<UCLModelAsset>();
    CF_INFO(TEXT("[CLAssetDefinition_Model] Loaded %d object(s)."), Assets.Num());

    if (Assets.Num() == 0)
    {
        CF_WARN(TEXT("[CLAssetDefinition_Model] No assets resolved by LoadObjects<UCLModelAsset>()."));
        return EAssetCommandResult::Unhandled;
    }

    for (UCLModelAsset* Asset : Assets)
    {
        if (!Asset)
        {
            CF_WARN(TEXT("[CLAssetDefinition_Model] -> Null asset, skipping."));
            continue;
        }

        CF_INFO(TEXT("[CLAssetDefinition_Model] -> Launch CLModelEditorToolkit for '%s' (Mode=%s)"),
            *Asset->GetName(),
            Mode == EToolkitMode::WorldCentric ? TEXT("WorldCentric") : TEXT("Standalone"));

        // *** Use the per-plugin thin subclass (branding/extension seam) ***
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
        CF_INFO(TEXT("[CLAssetDefinition_Model] -> RegisteredWithAssetEditorSubsystem=%s"),
            bHasEditor ? TEXT("YES") : TEXT("NO"));
#endif
    }

    CF_WARN(TEXT("[CLAssetDefinition_Model] <<< OpenAssets DONE"));
    return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE