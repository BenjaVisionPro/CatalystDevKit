// ============================================
// __PLUGIN_NAME__ Editor Widget (Header)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Minimal editor shell for __PLUGIN_NAME__.
 * Shows a logo button (top-left) and a big centered title: "__PLUGIN_NAME__ Editor".
 */
class S__PREFIX__ModelWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(S__PREFIX__ModelWidget) {}
        SLATE_ARGUMENT(int32, Seed) // kept for API compatibility (unused)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    // Logo button handler (no-op placeholder)
    FReply OnOpenSummary();

private:
    int32 PreviewSeed = 0;
};