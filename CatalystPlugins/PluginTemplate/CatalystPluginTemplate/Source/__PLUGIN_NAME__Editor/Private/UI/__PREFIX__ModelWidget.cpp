// ============================================
// __PLUGIN_NAME__ Editor Widget (Minimal)
// ============================================

#include "UI/__PREFIX__ModelWidget.h"

#include "Styling/AppStyle.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#include "__PREFIX__EditorStyle.h"   // plugin brushes (e.g. __PREFIX__.Logo64)

/* ---------- Construct ---------- */

void S__PREFIX__ModelWidget::Construct(const FArguments& InArgs)
{
    PreviewSeed = InArgs._Seed;

    ChildSlot
    [
        SNew(SBorder)
        .Padding(12.f)
        [
            SNew(SVerticalBox)

            // ===== Header: logo (left) =====
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)

                // Logo (clickable)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                [
                    SNew(SButton)
                    .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
                    .ContentPadding(0.f)
                    .OnClicked(this, &S__PREFIX__ModelWidget::OnOpenSummary)
                    [
                        SNew(SImage)
                        .Image(F__PREFIX__EditorStyle::Get().GetBrush("__PREFIX__.Logo64"))
                        .ToolTipText(NSLOCTEXT("__PREFIX__", "DashTitle", "Catalyst: Summary"))
                    ]
                ]

                // Fill spacer (keeps the header height)
                + SHorizontalBox::Slot()
                .FillWidth(1.f)
            ]

            // Divider
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.f, 8.f)
            [
                SNew(SSeparator)
            ]

            // ===== Centered title =====
            + SVerticalBox::Slot()
            .FillHeight(1.f)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
                SNew(SBorder)
                .Padding(FMargin(12.f))
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                [
                    SNew(STextBlock)
                    .Justification(ETextJustify::Center)
                    .Font(FCoreStyle::GetDefaultFontStyle("Regular", 32))
                    .Text(NSLOCTEXT("__PREFIX__", "EditorTitle", "__PLUGIN_NAME__ Editor"))
                ]
            ]
        ]
    ];
}

/* ---------- Actions (stub) ---------- */

FReply S__PREFIX__ModelWidget::OnOpenSummary()
{
    // Minimal template: nothing to do yet.
    return FReply::Handled();
}