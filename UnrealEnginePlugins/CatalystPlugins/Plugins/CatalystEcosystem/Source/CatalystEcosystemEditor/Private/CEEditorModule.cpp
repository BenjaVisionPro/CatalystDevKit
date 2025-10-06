// CEEEditorModule.cpp
// ============================================================================
// Catalyst Ecosystem — Editor Module (AssetDefinition-driven)
// ----------------------------------------------------------------------------
// - Registers "Catalyst:Ecosystem" Nomad tab + ToolMenus entry
// - Boots CE editor style/commands
// - Tab title uses Ecosystem Title if set, else "Catalyst:Ecosystem"
// - NOTE: Add(+)/Content Browser placement is handled by UAssetDefinition
//         (e.g., UCEAssetDefinition_Model::GetAssetCategories()).
// ============================================================================

#include "CEEditorModule.h"

#include "CEEditorStyle.h"
#include "CEEditorCommands.h"
#include "UI/SCEVisualizer.h"

#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

// For dynamic tab title lookup
#include "Model/CEModelAsset.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/UnrealType.h"

#include "Log/CFLog.h"                  // CF_* macros

// --- Diagnostics (UE 5.6-safe) ---
#include "AssetDefinitionDefault.h"     // UAssetDefinition
#include "Factories/Factory.h"          // UFactory

// --- Our concrete types (so we can query their CDOs safely) ---
#include "AssetDefinitions/CFAssetDefinition_Model.h"   // UCFAssetDefinition_Model (Foundation, Editor module)
#include "AssetDefinitions/CEAssetDefinition_Model.h"   // UCEAssetDefinition_Model (Ecosystem, Editor module)
#include "Factories/CEModelAssetFactory.h"              // UCEModelAssetFactory

DEFINE_LOG_CATEGORY(LogCEEditor);

// Menu namespace Connect created for the global Catalyst menu
static const FName CatalystMenuName("Catalyst.Plugins");
// Nomad tab name (internal)
static const FName CatalystEcosystemEditorTabName("Catalyst:Ecosystem");

static FDelegateHandle GToolMenusStartupHandle;

#define LOCTEXT_NAMESPACE "FCEEditorModule"

// ---------- Focused diagnostics: only our definitions/factory ----------
static void CE_DumpCreationPath()
{
    // 1) Foundation AssetDefinition
    {
        UClass* Cls = UCFAssetDefinition_Model::StaticClass();
        UObject* RawCDO = Cls->GetDefaultObject(false);
        UAssetDefinition* DefCDO = Cast<UAssetDefinition>(RawCDO);
        if (!IsValid(DefCDO))
        {
            CF_CAT_LOG(LogCEEditor, Warning, TEXT("[Diag/Def:CF] No valid CDO for %s"), *Cls->GetName());
        }
        else
        {
            const TSoftClassPtr<UObject> Soft = DefCDO->GetAssetClass();
            UClass* TargetLoaded = (!Soft.IsNull()) ? Soft.LoadSynchronous() : nullptr;

            const TConstArrayView<FAssetCategoryPath> Paths = DefCDO->GetAssetCategories();
            const int32 NumPaths = Paths.Num();

            CF_CAT_LOG(LogCEEditor, Display,
                TEXT("[Diag/Def:CF] %s -> Target=%s  CategoryPaths=%d"),
                *Cls->GetName(), *GetNameSafe(TargetLoaded), NumPaths);
        }
    }

    // 2) Ecosystem AssetDefinition
    {
        UClass* Cls = UCEAssetDefinition_Model::StaticClass();
        UObject* RawCDO = Cls->GetDefaultObject(false);
        UAssetDefinition* DefCDO = Cast<UAssetDefinition>(RawCDO);
        if (!IsValid(DefCDO))
        {
            CF_CAT_LOG(LogCEEditor, Warning, TEXT("[Diag/Def:CE] No valid CDO for %s"), *Cls->GetName());
        }
        else
        {
            const TSoftClassPtr<UObject> Soft = DefCDO->GetAssetClass();
            UClass* TargetLoaded = (!Soft.IsNull()) ? Soft.LoadSynchronous() : nullptr;

            const TConstArrayView<FAssetCategoryPath> Paths = DefCDO->GetAssetCategories();
            const int32 NumPaths = Paths.Num();

            CF_CAT_LOG(LogCEEditor, Display,
                TEXT("[Diag/Def:CE] %s -> Target=%s  CategoryPaths=%d"),
                *Cls->GetName(), *GetNameSafe(TargetLoaded), NumPaths);
        }
    }

    // 3) Ecosystem Factory CDO
    {
        UClass* Cls = UCEModelAssetFactory::StaticClass();
        UObject* RawCDO = Cls->GetDefaultObject(false);
        UFactory* FacCDO = Cast<UFactory>(RawCDO);
        if (!IsValid(FacCDO))
        {
            CF_CAT_LOG(LogCEEditor, Warning, TEXT("[Diag/Factory] No valid CDO for %s"), *Cls->GetName());
        }
        else
        {
            CF_CAT_LOG(LogCEEditor, Display,
                TEXT("[Diag/Factory] %s  SupportedClass=%s  ShouldShowInNewMenu=%s  MenuCat=%u"),
                *Cls->GetName(),
                *GetNameSafe(FacCDO->SupportedClass),
                FacCDO->ShouldShowInNewMenu() ? TEXT("true") : TEXT("false"),
                FacCDO->GetMenuCategories());
        }
    }
}
// ---------------------------------------------------------------------------

void FCEEditorModule::StartupModule()
{
    // Force-link our concrete classes so their UClass/CDOs exist before menus build.
    UCFAssetDefinition_Model::StaticClass();
    UCEAssetDefinition_Model::StaticClass();
    UCEModelAssetFactory::StaticClass();

    // Defer menu registration until ToolMenus is ready
    GToolMenusStartupHandle = UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCEEditorModule::RegisterMenus));

    // Style/commands
    FCEEditorStyle::Initialize();
    FCEEditorStyle::ReloadTextures();
    FCEEditorCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    // Nomad tab for visualizer/designer
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        CatalystEcosystemEditorTabName,
        FOnSpawnTab::CreateRaw(this, &FCEEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("CE_TabTitle_Default", "Catalyst:Ecosystem"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    CF_CAT_LOG(LogCEEditor, Display, TEXT("CatalystEcosystemEditor Startup"));

    // One-shot diagnostics: prove AssetDefinition + Factory wiring for Add(+)
    CE_DumpCreationPath();
}

void FCEEditorModule::ShutdownModule()
{
    // Unregister ToolMenus callback + ownership
    if (GToolMenusStartupHandle.IsValid())
    {
        UToolMenus::UnRegisterStartupCallback(GToolMenusStartupHandle);
        GToolMenusStartupHandle.Reset();
    }
    UToolMenus::UnregisterOwner(this);

    // Unregister Nomad tab
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystEcosystemEditorTabName);

    // Optional shutdowns if you own the lifetime
    // FCEEditorCommands::Unregister();
    // FCEEditorStyle::Shutdown();

    CF_CAT_LOG(LogCEEditor, Display, TEXT("CatalystEcosystemEditor Shutdown"));
}

void FCEEditorModule::RegisterMenus()
{
    UToolMenus* TM = UToolMenus::Get();
    if (!TM) return;

    // Extend the global Catalyst menu
    UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName);
    if (!Menu) return;

    FToolMenuSection& Sec = Menu->AddSection("CatalystEcosystem", LOCTEXT("CatalystEcosystem", "Catalyst:Ecosystem"));

    // Rebuild section dynamically on open
    Sec.AddDynamicEntry(
        "EcosystemEntries",
        FNewToolMenuSectionDelegate::CreateRaw(this, &FCEEditorModule::BuildEcosystemMenu));
}

void FCEEditorModule::BuildEcosystemMenu(FToolMenuSection& Section)
{
    const bool bVisualizerRunning = false; // TODO: wire up real state
    const FText Label = bVisualizerRunning
        ? LOCTEXT("OpenEcosystem_Running", "Ecosystem (Running)")
        : LOCTEXT("OpenEcosystem", "Ecosystem");

    Section.AddMenuEntry(
        "OpenEcosystemWindow",
        Label,
        LOCTEXT("OpenEcosystemDesc", "Open the Catalyst:Ecosystem editor/visualiser."),
        FSlateIcon(FCEEditorStyle::GetStyleSetName(), "CE.ToolbarIcon40"),
        FUIAction(FExecuteAction::CreateRaw(this, &FCEEditorModule::PluginButtonClicked)));
}

TSharedRef<SDockTab> FCEEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& Args)
{
    // Build tab with a dynamic label (ecosystem title if available)
    const FText TabLabel = GetEcosystemTabLabel();

    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        .Label(TabLabel)
        [
            SNew(SCEVisualizer)
            .Seed(1337) // placeholder default
        ];
}

void FCEEditorModule::PluginButtonClicked()
{
    CF_CAT_LOG(LogCEEditor, Display, TEXT("FCEEditorModule::PluginButtonClicked()"));
    FGlobalTabmanager::Get()->TryInvokeTab(CatalystEcosystemEditorTabName);
}

FText FCEEditorModule::GetEcosystemTabLabel() const
{
    // Default/fallback
    static const FText DefaultTitle = LOCTEXT("CE_TabTitle_Default", "Catalyst:Ecosystem");

    // Try to use the seed asset's title if available (reflection-based, safe if fields change)
    const FSoftObjectPath SeedPath(TEXT("/CatalystEcosystem/Model/CEModelAsset_Seed.CEModelAsset_Seed"));
    if (UCEModelAsset* Asset = Cast<UCEModelAsset>(SeedPath.TryLoad()))
    {
        // Look for UPROPERTY Model.Title via reflection (Title is optional)
        if (FProperty* ModelProp = Asset->GetClass()->FindPropertyByName(TEXT("Model")))
        {
            if (FStructProperty* StructProp = CastField<FStructProperty>(ModelProp))
            {
                void* ModelPtr = StructProp->ContainerPtrToValuePtr<void>(Asset);
                if (UScriptStruct* ModelStruct = StructProp->Struct)
                {
                    if (FProperty* TitleProp = ModelStruct->FindPropertyByName(TEXT("Title")))
                    {
                        if (FStrProperty* StrProp = CastField<FStrProperty>(TitleProp))
                        {
                            const FString Title = StrProp->GetPropertyValue_InContainer(ModelPtr);
                            if (!Title.IsEmpty())
                            {
                                return FText::FromString(Title);
                            }
                        }
                    }
                }
            }
        }

        // Otherwise, fall back to the asset name if present
        if (Asset->GetFName() != NAME_None)
        {
            return FText::FromName(Asset->GetFName());
        }
    }

    return DefaultTitle;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCEEditorModule, CatalystEcosystemEditor)