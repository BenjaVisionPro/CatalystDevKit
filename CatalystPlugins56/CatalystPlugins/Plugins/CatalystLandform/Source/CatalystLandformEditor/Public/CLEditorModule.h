// ============================================================================
// CatalystLandformEditor — Module interface (AssetDefinition-driven)
// ============================================================================

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

class UToolMenu;
struct FToolMenuSection;

// Editor log category (defined in the .cpp)
DECLARE_LOG_CATEGORY_EXTERN(LogCLLandformEditor, Log, All);

/**
 * Editor module for the Catalyst Landform plugin.
 * Handles menu registration, Nomad tab spawning, and diagnostics (debug only).
 * Add(+) placement is handled entirely by UAssetDefinition classes.
 */
class FCLEditorModule : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Opens the Landform editor/visualiser tab
	void PluginButtonClicked();

private:
	// Register the "Catalyst" → "Landform" menu section
	void RegisterMenus();

	// Populate the section dynamically each time it opens
	void BuildLandformMenu(FToolMenuSection& Section);

	// Spawn the Landform editor tab
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

	// Resolve tab title (Landform Title or fallback)
	FText GetLandformTabLabel() const;

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};