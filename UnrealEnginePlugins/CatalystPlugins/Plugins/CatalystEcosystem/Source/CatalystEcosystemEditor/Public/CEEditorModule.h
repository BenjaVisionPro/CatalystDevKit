// CEEEditorModule.h

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UToolMenu;
struct FToolMenuSection;

DECLARE_LOG_CATEGORY_EXTERN(LogCEEditor, Log, All);

class FCEEditorModule : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Opens the Ecosystem editor/visualiser tab
	void PluginButtonClicked();

private:
	// Contribute to the global Catalyst menu
	void RegisterMenus();

	// Build the Ecosystem section dynamically each time the menu opens
	void BuildEcosystemMenu(FToolMenuSection& Section);

	// Spawn the Ecosystem editor tab (Nomad tab)
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

	// Resolve a nice window title: Ecosystem Title (if available) or fallback.
	FText GetEcosystemTabLabel() const;

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// Keep strong refs so we can unregister AssetTypeActions on shutdown
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredAssetTypeActions;
};