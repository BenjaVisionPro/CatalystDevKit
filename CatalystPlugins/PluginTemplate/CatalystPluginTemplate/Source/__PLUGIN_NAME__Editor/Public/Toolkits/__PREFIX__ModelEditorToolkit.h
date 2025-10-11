#pragma once
#include "Toolkits/CFModelEditorToolkit.h"

/**
 * Thin wrapper over Foundation's FCFModelEditorToolkit.
 * Today: only branding (toolkit name/IDs).
 * Future: override layout, add tabs/actions per plugin.
 */
class F__PREFIX__ModelEditorToolkit : public FCFModelEditorToolkit
{
public:
    virtual FName GetToolkitFName() const override
    {
        return FName(TEXT("__PREFIX__Editor")); // e.g., "CLEditor"
    }

    virtual FText GetBaseToolkitName() const override
    {
        return NSLOCTEXT("__PREFIX__", "ToolkitName", "__PLUGIN_DISPLAY_NAME__ Editor");
        // e.g., "Landform Editor"
    }

    // Optional: shows in world-centric titles
    virtual FString GetWorldCentricTabPrefix() const override
    {
        return TEXT("__PLUGIN_DISPLAY_NAME__"); // e.g., "Landform"
    }
};