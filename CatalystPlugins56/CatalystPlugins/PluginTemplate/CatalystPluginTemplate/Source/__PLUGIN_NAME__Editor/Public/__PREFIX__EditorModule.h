// ============================================================================
// __PLUGIN_NAME__Editor — Module interface (AssetDefinition-driven)
// ============================================================================

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

class UToolMenu;
struct FToolMenuSection;

// Editor log category (defined in the .cpp)
DECLARE_LOG_CATEGORY_EXTERN(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Log, All);

/**
 * Editor module for the Catalyst __PLUGIN_DISPLAY_NAME__ plugin.
 * Handles menu registration, Nomad tab spawning, and diagnostics (debug only).
 * Add(+) placement is handled entirely by UAssetDefinition classes.
 */
class F__PREFIX__EditorModule : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Opens the __PLUGIN_DISPLAY_NAME__ editor/visualiser tab
	void PluginButtonClicked();

private:
	// Register the "Catalyst" → "__PLUGIN_DISPLAY_NAME__" menu section
	void RegisterMenus();

	// Populate the section dynamically each time it opens
	void Build__PLUGIN_DISPLAY_NAME__Menu(FToolMenuSection& Section);

	// Spawn the __PLUGIN_DISPLAY_NAME__ editor tab
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

	// Resolve tab title (__PLUGIN_DISPLAY_NAME__ Title or fallback)
	FText Get__PLUGIN_DISPLAY_NAME__TabLabel() const;

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};