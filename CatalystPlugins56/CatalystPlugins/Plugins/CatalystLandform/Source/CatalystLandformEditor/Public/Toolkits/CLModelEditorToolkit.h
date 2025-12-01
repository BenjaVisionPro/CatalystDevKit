#pragma once
#include "Toolkits/CFModelEditorToolkit.h"

/**
 * Thin wrapper over Foundation's FCFModelEditorToolkit.
 * Today: only branding (toolkit name/IDs).
 * Future: override layout, add tabs/actions per plugin.
 */
class FCLModelEditorToolkit : public FCFModelEditorToolkit
{
public:
    virtual FName GetToolkitFName() const override
    {
        return FName(TEXT("CLEditor")); // e.g., "CLEditor"
    }

    virtual FText GetBaseToolkitName() const override
    {
        return NSLOCTEXT("CL", "ToolkitName", "Landform Editor");
        // e.g., "Landform Editor"
    }

    // Optional: shows in world-centric titles
    virtual FString GetWorldCentricTabPrefix() const override
    {
        return TEXT("Landform"); // e.g., "Landform"
    }
};