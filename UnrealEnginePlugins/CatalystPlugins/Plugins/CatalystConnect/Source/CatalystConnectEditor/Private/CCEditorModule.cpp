// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CCEditorModule.h"

#include "CCHeaders.h"
#include "Styles/CFEditorFontsStyle.h"
#include "CCEditorStyle.h"
#include "CCEditorCommands.h"

#include "LevelEditor.h"
#include "ToolMenus.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"

DEFINE_LOG_CATEGORY(LogCCEditor);

static const FName CatalystMenuName("Catalyst.Plugins");
static const FName CatalystConnectEditorTabName("Catalyst:Connect Designer");

#define LOCTEXT_NAMESPACE "FCCEditorModule"

void FCCEditorModule::StartupModule()
{
    // Register global Catalyst menu + Connect’s entries
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCCEditorModule::RegisterMenus));

    FCFEditorFontsStyle::Initialize();
    
    FCCEditorStyle::Initialize();
    FCCEditorStyle::ReloadTextures();
    FCCEditorCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

    // Map commands and extend toolbar with the Catalyst Plugins dropdown
    {
        auto EditorCommand = FCCEditorCommands::Get();

        PluginCommands->MapAction(
            EditorCommand.OpenPluginWindow,
            FExecuteAction::CreateRaw(this, &FCCEditorModule::PluginButtonClicked),
            FCanExecuteAction());

        TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
        ToolbarExtender->AddToolBarExtension(
            "Play",
            EExtensionHook::After,
            PluginCommands,
            FToolBarExtensionDelegate::CreateRaw(this, &FCCEditorModule::AddEditorToolsToToolbarExtension));

        LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
        LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());
    }

    // Settings (unchanged)
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "Catalyst:Connect",
            LOCTEXT("CCSettingsName", "Catalyst:Connect"),
            LOCTEXT("CCSettingsDescription", "Catalyst:Connect Settings"),
            GetMutableDefault<UCCSettings>());

        SettingsModule->RegisterSettings("Project", "Plugins", "Catalyst:Connect Editor",
            LOCTEXT("CCSettingsNameEd", "Catalyst:Connect Editor"),
            LOCTEXT("CCSettingsDescriptionEd", "Catalyst:Connect Editor Settings"),
            GetMutableDefault<UCCEditorSettings>());
    }

    // Nomad tab for Connect designer
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        CatalystConnectEditorTabName,
        FOnSpawnTab::CreateRaw(this, &FCCEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FCatalystConnectEditorTabTitle", "CatalystConnectEditor"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCCEditorModule::ShutdownModule()
{
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);

    FCCEditorStyle::Shutdown();
    FCCEditorCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystConnectEditorTabName);

    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "Catalyst:Connect");
        SettingsModule->UnregisterSettings("Project", "Plugins", "Catalyst:Connect Editor");
    }
}

FCCEditorModule& FCCEditorModule::Get()
{
    return FModuleManager::Get().GetModuleChecked<FCCEditorModule>(TEXT("CCEditor"));
}

void FCCEditorModule::AddEditorToolsToToolbarExtension(FToolBarBuilder& Builder)
{
    Builder.BeginSection("CatalystPlugins");
    {
        // UE 5.6 toolbar combo expects FOnGetContent (returns SWidget). Render the ToolMenu widget here.
        Builder.AddComboButton(
            FUIAction(),
            FOnGetContent::CreateLambda([]() -> TSharedRef<SWidget>
            {
                return UToolMenus::Get()->GenerateWidget(CatalystMenuName, FToolMenuContext());
            }),
            LOCTEXT("CCTools", "Catalyst Plugins"),
            LOCTEXT("CCEditorTools", "Catalyst Plugins"),
            FSlateIcon(FCCEditorStyle::GetStyleSetName(), "CCEditor.EditorTools"));
    }
    Builder.EndSection();
}

void FCCEditorModule::RegisterMenus()
{
    UToolMenus* TM = UToolMenus::Get();

    // Create the global Catalyst menu once
    if (!TM->IsMenuRegistered(CatalystMenuName))
    {
        UToolMenu* Menu = TM->RegisterMenu(CatalystMenuName);
        Menu->AddSection("CatalystBase", LOCTEXT("CatalystBase", "Catalyst Plugins"));
    }

    // Connect contributes its entries dynamically (rebuilt every open)
    UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName);
    FToolMenuSection& Sec = Menu->AddSection("CatalystConnect", LOCTEXT("CatalystConnect", "Catalyst:Connect"));

    // Modern delegate: void(FToolMenuSection&)
    Sec.AddDynamicEntry(
        "ConnectEntries",
        FNewToolMenuSectionDelegate::CreateRaw(this, &FCCEditorModule::BuildConnectMenu)
    );
}

void FCCEditorModule::BuildConnectMenu(FToolMenuSection& Section)
{
    Section.AddMenuEntry(
        "OpenConnectWindow",
        LOCTEXT("OpenConnect", "Open Connect"),
        LOCTEXT("OpenConnectDesc", "Open the Catalyst:Connect designer/visualiser."),
        FSlateIcon(FCCEditorStyle::GetStyleSetName(), "CCEditor.EditorTools"),
        FUIAction(FExecuteAction::CreateRaw(this, &FCCEditorModule::PluginButtonClicked)));
}

TSharedRef<SDockTab> FCCEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    const FText WidgetText = FText::Format(
        LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
        FText::FromString(TEXT("FCCEditorModule::OnSpawnPluginTab")),
        FText::FromString(TEXT("CatalystConnectEditor.cpp")));

    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SBox)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(WidgetText)
            ]
        ];
}

void FCCEditorModule::PluginButtonClicked()
{
    UE_LOG(LogCCEditor, Warning, TEXT("FCCEditorModule::PluginButtonClicked()"));
    FGlobalTabmanager::Get()->TryInvokeTab(CatalystConnectEditorTabName);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCCEditorModule, CatalystConnectEditor)
