// ============================================
// CatalystLandform Editor Widget (Minimal)
// ============================================

#include "UI/CLModelWidget.h"

#include "Styling/AppStyle.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#include "CLEditorStyle.h"   // plugin brushes (e.g. CL.Logo64)

/* ---------- Construct ---------- */

void SCLModelWidget::Construct(const FArguments& InArgs)
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
                    .OnClicked(this, &SCLModelWidget::OnOpenSummary)
                    [
                        SNew(SImage)
                        .Image(FCLEditorStyle::Get().GetBrush("CL.Logo64"))
                        .ToolTipText(NSLOCTEXT("CL", "DashTitle", "Catalyst: Summary"))
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
                    .Text(NSLOCTEXT("CL", "EditorTitle", "CatalystLandform Editor"))
                ]
            ]
        ]
    ];
}

/* ---------- Actions (stub) ---------- */

FReply SCLModelWidget::OnOpenSummary()
{
    // Minimal template: nothing to do yet.
    return FReply::Handled();
}