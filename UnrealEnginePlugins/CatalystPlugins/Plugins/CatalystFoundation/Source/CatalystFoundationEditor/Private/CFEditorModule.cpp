// ============================================================================
// CatalystFoundationEditor — Editor Module (AssetDefinition-driven)
// ============================================================================

#include "CFEditorModule.h"
#include "Modules/ModuleManager.h"

// Define the editor log category once, here.
DEFINE_LOG_CATEGORY(LogCFEditor);

// ----------------------------------------------------------------------------
// NOTE:
//  - Legacy AssetTools-based category registration has been removed.
//  - Top-level Add menu placement is now provided by UAssetDefinition classes
//    (e.g., UCFAssetDefinition_Model::GetAssetCategories()).
// ----------------------------------------------------------------------------

void FCatalystFoundationEditorModule::StartupModule()
{
	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Startup"));
}

void FCatalystFoundationEditorModule::ShutdownModule()
{
	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Shutdown"));
}

// Implement the module (only in the .cpp!)
IMPLEMENT_MODULE(FCatalystFoundationEditorModule, CatalystFoundationEditor)