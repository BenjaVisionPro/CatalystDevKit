// ============================================================================
// CatalystFoundationEditor — Editor Module (AssetDefinition-driven)
// ----------------------------------------------------------------------------
// Clean, no AssetTools category registration. AssetDefinitions own Add(+).
// ============================================================================

#include "CFEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Log/CFLog.h" // CF_* macros

DEFINE_LOG_CATEGORY(LogCFEditor);

void FCatalystFoundationEditorModule::StartupModule()
{
    CF_CAT_LOG(LogCFEditor, Display, TEXT("CatalystFoundationEditor Startup"));
}

void FCatalystFoundationEditorModule::ShutdownModule()
{
    CF_CAT_LOG(LogCFEditor, Display, TEXT("CatalystFoundationEditor Shutdown"));
}

IMPLEMENT_MODULE(FCatalystFoundationEditorModule, CatalystFoundationEditor)