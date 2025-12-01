#include "CFEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Log/CFLog.h"
#include "CFEditorCommands.h"

DEFINE_LOG_CATEGORY(LogCFEditor);

void FCatalystFoundationEditorModule::StartupModule()
{
	FCFEditorCommands::Register();
	CF_CAT_LOG(LogCFEditor, Display, TEXT("CatalystFoundationEditor Startup"));
}

void FCatalystFoundationEditorModule::ShutdownModule()
{
	FCFEditorCommands::Unregister();
	CF_CAT_LOG(LogCFEditor, Display, TEXT("CatalystFoundationEditor Shutdown"));
}

IMPLEMENT_MODULE(FCatalystFoundationEditorModule, CatalystFoundationEditor)