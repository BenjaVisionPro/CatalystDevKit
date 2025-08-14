// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CCEditorModule.h"

#include "CCHeaders.h"

#include "CCEditorStyle.h"
#include "CCEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"

DEFINE_LOG_CATEGORY(LogCCEditor);

static const FName CatalystConnectEditorTabName("Catalyst:Connect Designer");

#define LOCTEXT_NAMESPACE "FCCEditorModule"

void FCCEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCCEditorStyle::Initialize();
	FCCEditorStyle::ReloadTextures();

	FCCEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// Editor Tools
	{
		auto editorCommand = FCCEditorCommands::Get();
		
		PluginCommands->MapAction(
			editorCommand.OpenPluginWindow,
			FExecuteAction::CreateRaw(this, &FCCEditorModule::PluginButtonClicked),
			FCanExecuteAction());
			
		TSharedPtr<FExtender> toolbarExtender = MakeShareable(new FExtender);
		toolbarExtender->AddToolBarExtension("Play", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FCCEditorModule::AddEditorToolsToToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(toolbarExtender);
		LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());	
	}
	
	// SettingsModule
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->RegisterSettings("Project", "Plugins", "Catalyst:Connect",
				LOCTEXT("CCSettingsName", "Catalyst:Connect"),
				LOCTEXT("CCSettingsDescription", "Catalyst:Connect Settings"),
				GetMutableDefault<UCCSettings>());
			SettingsModule->RegisterSettings("Project", "Plugins", "Catalyst:Connect Editor",
				LOCTEXT("CCSettingsName", "Catalyst:Connect Editor"),
				LOCTEXT("CCSettingsDescription", "Catalyst:Connect Editor Settings"),
				GetMutableDefault<UCCEditorSettings>());
		}
	}
	
	//UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCCEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CatalystConnectEditorTabName, FOnSpawnTab::CreateRaw(this, &FCCEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCatalystConnectEditorTabTitle", "CatalystConnectEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCCEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FCCEditorStyle::Shutdown();
	FCCEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystConnectEditorTabName);
	
	// Unregister Settings
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "Catalyst:Connect");
			SettingsModule->UnregisterSettings("Project", "Plugins", "Catalyst:Connect Editor");
		}
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
		Builder.AddComboButton(
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FCCEditorModule::MakeCatalystPluginsMenu, true, true, true, true, true, true),
			LOCTEXT("CCTools", "Catalyst Plugins"),
			LOCTEXT("CCEditorTools", "Catalyst Plugins"),
			FSlateIcon(FCCEditorStyle::GetStyleSetName(), "CCEditor.EditorTools")
		);
	}
	Builder.EndSection();
}

TSharedRef<SWidget> FCCEditorModule::MakeCatalystPluginsMenu(bool InitialSetup, bool ComponentAction, bool OpenWindow, bool PreviewInViewport, bool EditorCameraControl, bool Others)
{
    UE_LOG(LogCCEditor, Warning, TEXT("FCCEditorModule::MakeCatalystPluginsMenu()"));
    FMenuBuilder MenuBuilder(true, PluginCommands);
	auto commandList = FCCEditorCommands::Get();

	// Connection
	{
		MenuBuilder.BeginSection("CatalystConnect", LOCTEXT("CatalystConnect", "Catalyst:Connect"));
		{
            MenuBuilder.AddMenuEntry(
                commandList.OpenPluginWindow,
                FName("OpenPlugin"),
                commandList.OpenPluginWindow->GetLabel(),
                commandList.OpenPluginWindow->GetDescription(),
                FSlateIcon(FCCEditorStyle::GetStyleSetName(), "CCEditor.EditorTools")
            );
        }
	}
	
	return MenuBuilder.MakeWidget();
}

TSharedRef<SDockTab> FCCEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCCEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CatalystConnectEditor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
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
