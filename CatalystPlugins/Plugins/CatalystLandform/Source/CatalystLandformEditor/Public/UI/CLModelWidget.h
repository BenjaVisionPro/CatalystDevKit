// ============================================
// CatalystLandform Editor Widget (Header)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Minimal editor shell for CatalystLandform.
 * Shows a logo button (top-left) and a big centered title: "CatalystLandform Editor".
 */
class SCLModelWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCLModelWidget) {}
        SLATE_ARGUMENT(int32, Seed) // kept for API compatibility (unused)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    // Logo button handler (no-op placeholder)
    FReply OnOpenSummary();

private:
    int32 PreviewSeed = 0;
};