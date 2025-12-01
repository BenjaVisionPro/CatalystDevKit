#include "UI/Panels/SCESummaryPanel.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Styling/SlateTypes.h"

#include "Styles/CFEditorFontsStyle.h"

void SCESummaryPanel::Construct(const FArguments& InArgs)
{
    SCFAbstractPanel::Construct(
        SCFAbstractPanel::FArguments()
        .Title(InArgs._Title)
        .Content()
        [
            BuildSummaryBody()
        ]
    );
}

TSharedRef<SWidget> SCESummaryPanel::BuildSummaryBody()
{
    return SNew(SVerticalBox)
    + SVerticalBox::Slot()
    .AutoHeight()
    .Padding(8.f, 8.f, 8.f, 4.f)
    [
        SNew(STextBlock)
        .Font(FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::FontDisplay32))
        .Text(FText::FromString(TEXT("Summary / News")))
    ]
    + SVerticalBox::Slot()
    .FillHeight(1.f)
    .Padding(8.f, 4.f, 8.f, 8.f)
    [
        SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.DarkGroupBorder"))
        [
            SNew(SScrollBox)
            + SScrollBox::Slot()
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("Welcome to Catalyst:Ecosystem. Latest events, logs, and notices will appear here.")))
            ]
        ]
    ];
}
