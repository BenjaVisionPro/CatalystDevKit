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
DECLARE_LOG_CATEGORY_EXTERN(LogCEEditor, Log, All);

/**
 * Editor module for the Catalyst Ecosystem plugin.
 * Handles menu registration, Nomad tab spawning, and diagnostics (debug only).
 * Add(+) placement is handled entirely by UAssetDefinition classes.
 */
class F__PREFIX__EditorModule : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Opens the Ecosystem editor/visualiser tab
	void PluginButtonClicked();

private:
	// Register the "Catalyst" → "Ecosystem" menu section
	void RegisterMenus();

	// Populate the section dynamically each time it opens
	void BuildEcosystemMenu(FToolMenuSection& Section);

	// Spawn the Ecosystem editor tab
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

	// Resolve tab title (Ecosystem Title or fallback)
	FText GetEcosystemTabLabel() const;

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};