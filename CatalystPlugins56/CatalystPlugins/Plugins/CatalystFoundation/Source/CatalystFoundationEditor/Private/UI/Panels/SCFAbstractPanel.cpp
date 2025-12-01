#include "UI/Panels/SCFAbstractPanel.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/SlateTypes.h"

#include "Styles/CFEditorFontsStyle.h"

void SCFAbstractPanel::Construct(const FArguments& InArgs)
{
    Title = InArgs._Title;

    // Read default slot: it's an Arguments container with a .Widget TSharedPtr<SWidget>
    const TSharedPtr<SWidget> BodyPtr = InArgs._Content.Widget;
    const TSharedRef<SWidget> Body    = BodyPtr.IsValid() ? BodyPtr.ToSharedRef() : SNullWidget::NullWidget;

    const TSharedPtr<SWidget> ToolbarContent = InArgs._Toolbar;

    ChildSlot
    [
        WrapInChrome(Title.Get(FText::GetEmpty()), Body, ToolbarContent)
    ];
}

TSharedRef<SWidget> SCFAbstractPanel::WrapInChrome(const FText& InTitle,
                                                   TSharedRef<SWidget> Body,
                                                   TSharedPtr<SWidget> ToolbarContent)
{
    return SNew(SBorder)
    .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
    [
        SNew(SVerticalBox)

        // Title row
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(8.f, 6.f)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .FillWidth(1.f)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Font(FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::FontDisplay32))
                .Text(InTitle)
            ]
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                ToolbarContent.IsValid() ? ToolbarContent.ToSharedRef() : SNullWidget::NullWidget
            ]
        ]

        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SSeparator)
        ]

        // Body
        + SVerticalBox::Slot()
        .FillHeight(1.f)
        .Padding(8.f)
        [
            Body
        ]
    ];
}
