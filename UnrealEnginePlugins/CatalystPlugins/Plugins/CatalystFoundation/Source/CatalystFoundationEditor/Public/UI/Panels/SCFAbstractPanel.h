#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Export from the *editor* module
class CATALYSTFOUNDATIONEDITOR_API SCFAbstractPanel : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCFAbstractPanel) {}
        SLATE_ATTRIBUTE(FText, Title)
        // Single optional widget, not a slot array:
        SLATE_ARGUMENT(TSharedPtr<SWidget>, Toolbar)
        // Default unnamed content (the body)
        SLATE_DEFAULT_SLOT(FArguments, Content)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

protected:
    TSharedRef<SWidget> WrapInChrome(const FText& InTitle,
                                     TSharedRef<SWidget> Body,
                                     TSharedPtr<SWidget> ToolbarContent);

protected:
    TAttribute<FText> Title;
};
