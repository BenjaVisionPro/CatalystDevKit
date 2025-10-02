// CEEEditorModule.h  (adjust filename to your module header)

// ============================================
// Copyright © ...
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UToolMenu;
struct FToolMenuSection;

DECLARE_LOG_CATEGORY_EXTERN(LogCFEditor, Log, All);

class FCFEditorModule : public IModuleInterface
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

    // Spawn the Ecosystem editor tab (if you expose a Nomad tab)
    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

private:
    TSharedPtr<class FUICommandList> PluginCommands;
};
