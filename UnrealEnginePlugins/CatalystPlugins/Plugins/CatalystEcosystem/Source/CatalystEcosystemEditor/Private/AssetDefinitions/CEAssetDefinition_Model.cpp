#include "AssetDefinitions/CEAssetDefinition_Model.h"
#include "Model/CEModelAsset.h"
#include "Toolkits/CFModelEditorToolkit.h"
#include "Log/CFLog.h"

// Extra diagnostics
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define LOCTEXT_NAMESPACE "CEAssetDefinition_Model"

FText UCEAssetDefinition_Model::GetAssetDisplayName() const
{
    return LOCTEXT("CE_Ecosystem_DisplayName", "Ecosystem");
}

FLinearColor UCEAssetDefinition_Model::GetAssetColor() const
{
    return FLinearColor(0.30f, 0.60f, 0.90f);
}

TSoftClassPtr<UObject> UCEAssetDefinition_Model::GetAssetClass() const
{
    CF_INFO(TEXT("[CEAssetDefinition_Model] GetAssetClass -> CEModelAsset"));
    return UCEModelAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UCEAssetDefinition_Model::GetAssetCategories() const
{
    static const FText Root = LOCTEXT("CatalystTopCat", "Catalyst");
    static const FText Mid  = LOCTEXT("CatalystSubCat_Ecosystems", "Ecosystems");

    static const FAssetCategoryPath RootToMid(Root, Mid);
    static const FAssetCategoryPath Paths[] = { RootToMid };

    CF_INFO(TEXT("[CEAssetDefinition_Model] GetAssetCategories -> [Catalyst/Ecosystems]"));
    return Paths;
}

EAssetCommandResult UCEAssetDefinition_Model::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    CF_WARN(TEXT("[CEAssetDefinition_Model] >>> OpenAssets CALLED"));
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
    const TArray<UCEModelAsset*> Assets = OpenArgs.LoadObjects<UCEModelAsset>();
    CF_INFO(TEXT("[CEAssetDefinition_Model] Loaded %d object(s)."), Assets.Num());

    if (Assets.Num() == 0)
    {
        CF_WARN(TEXT("[CEAssetDefinition_Model] No assets resolved by LoadObjects<UCEModelAsset>()."));
        return EAssetCommandResult::Unhandled;
    }

    for (UCEModelAsset* Asset : Assets)
    {
        if (!Asset)
        {
            CF_WARN(TEXT("[CEAssetDefinition_Model] -> Null asset, skipping."));
            continue;
        }

        CF_INFO(TEXT("[CEAssetDefinition_Model] -> Launch CFModelEditorToolkit for '%s' (Mode=%s)"),
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
        CF_INFO(TEXT("[CEAssetDefinition_Model] -> RegisteredWithAssetEditorSubsystem=%s"),
            bHasEditor ? TEXT("YES") : TEXT("NO"));
    }

    CF_WARN(TEXT("[CEAssetDefinition_Model] <<< OpenAssets DONE"));
    return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE