// CEEditorModule.cpp  (adjust filename to your module source)

#include "CEEditorModule.h"
#include "CEEditorStyle.h"
#include "CEEditorCommands.h"
#include "UI/SCEVisualizer.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

// If you have your own style/commands, include them:
// #include "CEEditorStyle.h"
// #include "CEEditorCommands.h"

DEFINE_LOG_CATEGORY(LogCEEditor);

static const FName CatalystMenuName("Catalyst.Plugins");

// 🔁 Replace with your actual tab name if you expose a Nomad tab:
static const FName CatalystEcosystemEditorTabName("Catalyst:Ecosystem Designer");

#define LOCTEXT_NAMESPACE "FCEEditorModule"

void FCEEditorModule::StartupModule()
{
    // Register our menu contributions after ToolMenus initializes
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCEEditorModule::RegisterMenus));

    FCEEditorStyle::Initialize();
    FCEEditorStyle::ReloadTextures();
    FCEEditorCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    // Optional: register a Nomad tab for the Ecosystem designer
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        CatalystEcosystemEditorTabName,
        FOnSpawnTab::CreateRaw(this, &FCEEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("CE_TabTitle", "Catalyst:Ecosystem"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCEEditorModule::ShutdownModule()
{
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);

    // Optional: CEEditorStyle::Shutdown();
    // CEEditorCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystEcosystemEditorTabName);
}

void FCEEditorModule::RegisterMenus()
{
    UToolMenus* TM = UToolMenus::Get();

    // Extend the global menu Connect created
    UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName);

    // Our own section
    FToolMenuSection& Sec = Menu->AddSection("CatalystEcosystem", LOCTEXT("CatalystEcosystem", "Catalyst:Ecosystem"));

    // Dynamically rebuild each time the menu opens (correct modern signature)
    Sec.AddDynamicEntry(
        "EcosystemEntries",
        FNewToolMenuSectionDelegate::CreateRaw(this, &FCEEditorModule::BuildEcosystemMenu)
    );
}

void FCEEditorModule::BuildEcosystemMenu(FToolMenuSection& Section)
{
    // Example dynamic status label (replace with your real signal)
    const bool bVisualizerRunning = false; // TODO: query your runtime/editor state
    const FText Label = bVisualizerRunning
        ? LOCTEXT("OpenEcosystem_Running", "Ecosystem (Running)")
        : LOCTEXT("OpenEcosystem", "Ecosystem");

    Section.AddMenuEntry(
        "OpenEcosystemWindow",
        Label,
        LOCTEXT("OpenEcosystemDesc", "Open the Catalyst:Ecosystem editor/visualiser."),
        FSlateIcon(FCEEditorStyle::GetStyleSetName(), "CE.ToolbarIcon40"),
        FUIAction(FExecuteAction::CreateRaw(this, &FCEEditorModule::PluginButtonClicked))
    );
}

TSharedRef<SDockTab> FCEEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
            .TabRole(ETabRole::NomadTab)
            [
                SNew(SCEVisualizer)
                .Seed(1337) // placeholder default; we can later pull from settings
            ];
}

void FCEEditorModule::PluginButtonClicked()
{
    UE_LOG(LogCEEditor, Log, TEXT("FCEEditorModule::PluginButtonClicked()"));
    FGlobalTabmanager::Get()->TryInvokeTab(CatalystEcosystemEditorTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCEEditorModule, CatalystEcosystemEditor)
