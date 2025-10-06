// ============================================================================
// CatalystFoundationEditor — Editor Module (AssetDefinition-driven)
// ============================================================================

#include "CFEditorModule.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h" // <-- Add this include

// Define the editor log category once, here.
DEFINE_LOG_CATEGORY(LogCFEditor);

void FCatalystFoundationEditorModule::StartupModule()
{
	// Register top-level "Catalyst" category for AssetDefinition Add(+)
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().RegisterAdvancedAssetCategory(
		FName(TEXT("Catalyst")),
		NSLOCTEXT("CatalystFoundationEditor", "CatalystAssetCategory", "Catalyst")
	);

	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Startup (registered 'Catalyst' category)"));
}

void FCatalystFoundationEditorModule::ShutdownModule()
{
	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Shutdown"));
}

IMPLEMENT_MODULE(FCatalystFoundationEditorModule, CatalystFoundationEditor)