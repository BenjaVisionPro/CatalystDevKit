#pragma once

#include "CoreMinimal.h"
#include "UI/Panels/SCFAbstractPanel.h"

// Simple summary/news panel
class CATALYSTECOSYSTEMEDITOR_API SCESummaryPanel : public SCFAbstractPanel
{
public:
    SLATE_BEGIN_ARGS(SCESummaryPanel) {}
        SLATE_ATTRIBUTE(FText, Title)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedRef<SWidget> BuildSummaryBody();
};
