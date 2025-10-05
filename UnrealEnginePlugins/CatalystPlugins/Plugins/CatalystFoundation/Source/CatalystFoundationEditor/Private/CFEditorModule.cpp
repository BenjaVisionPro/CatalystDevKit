// ============================================================================
// CatalystFoundationEditor — Module & Asset Category Registration
// ============================================================================

#include "CFEditorModule.h"
#include "AssetToolsModule.h"
#include "Modules/ModuleManager.h"

// Define the editor log category once, here.
DEFINE_LOG_CATEGORY(LogCFEditor);

// Initialize to Misc as a sentinel so we can detect first-time registration.
EAssetTypeCategories::Type FCFEditorAssetCategory::CatalystCategory = EAssetTypeCategories::Misc;

EAssetTypeCategories::Type FCFEditorAssetCategory::Get()
{
	return CatalystCategory;
}

void FCFEditorAssetCategory::Register()
{
	// Skip if already registered (hot-reload safe).
	if (CatalystCategory != EAssetTypeCategories::Misc)
	{
		return;
	}

	// Register top-level "Catalyst" category.
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	IAssetTools& AssetTools = AssetToolsModule.Get();

	CatalystCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName(TEXT("Catalyst")),
		NSLOCTEXT("CatalystFoundationEditor", "CatalystAssetCategory", "Catalyst"));

	UE_LOG(LogCFEditor, Log, TEXT("Registered 'Catalyst' asset category (mask=%d)."),
		static_cast<int32>(CatalystCategory));
}

// --- Module ---

void FCatalystFoundationEditorModule::StartupModule()
{
	FCFEditorAssetCategory::Register();
	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Startup"));
}

void FCatalystFoundationEditorModule::ShutdownModule()
{
	// No explicit unregistration for advanced categories.
	UE_LOG(LogCFEditor, Log, TEXT("CatalystFoundationEditor Shutdown"));
}

// Implement the module (only in the .cpp!)
IMPLEMENT_MODULE(FCatalystFoundationEditorModule, CatalystFoundationEditor)