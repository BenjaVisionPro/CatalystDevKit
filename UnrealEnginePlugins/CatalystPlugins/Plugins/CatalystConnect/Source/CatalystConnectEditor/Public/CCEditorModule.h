// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
struct FToolMenuSection; // forward-declare the struct used by ToolMenus section delegate

DECLARE_LOG_CATEGORY_EXTERN(LogCCEditor, Log, All);

class FCCEditorModule : public IModuleInterface
{
public:
    // IModuleInterface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // Singleton accessor
    static FCCEditorModule& Get();

    // Command action (opens the Connect designer tab)
    void PluginButtonClicked();

private:
    // Register the global Catalyst menu and add Connect-specific entries
    void RegisterMenus();

    // Build the Catalyst:Connect section dynamically each time the menu opens
    void BuildConnectMenu(FToolMenuSection& Section);

    // Add toolbar combo button that renders the ToolMenus-driven popup
    void AddEditorToolsToToolbarExtension(FToolBarBuilder& Builder);

    // Spawn the Connect editor tab
    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
    TSharedPtr<class FUICommandList> PluginCommands;
};
