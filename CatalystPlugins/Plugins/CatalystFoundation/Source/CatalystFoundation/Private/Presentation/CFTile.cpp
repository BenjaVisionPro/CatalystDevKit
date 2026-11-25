#include "Presentation/CFTile.h"

#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SNullWidget.h"

UCFTile::UCFTile()
{
    SetClipping(EWidgetClipping::ClipToBounds);
}

void UCFTile::SetVisualState(float InFocusProgress, float InOpacity)
{
    FocusProgress = FMath::Clamp(InFocusProgress, 0.f, 1.f);
    SetRenderOpacity(FMath::Clamp(InOpacity, 0.f, 1.f));
    if (Surface)
    {
        Surface->Invalidate(EInvalidateWidgetReason::Paint);
    }
}

TSharedRef<SWidget> UCFTile::RebuildWidget()
{
    const auto* Brush = FCoreStyle::Get().GetBrush("WhiteBrush");
    SAssignNew(Surface, SBorder)
        .BorderImage(Brush)
        .BorderBackgroundColor_Lambda([this] {
            return FSlateColor(FMath::Lerp(Style.Background, Style.FocusedBackground, FocusProgress));
        })
        .Padding(0)
        [BuildTileContent()];

    const auto Edge = [this, Brush](bool bVertical)
    {
        auto Box = SNew(SBox)
        [
            SNew(SBorder).Padding(0).BorderImage(Brush)
            .BorderBackgroundColor_Lambda([this] { return FSlateColor(Style.Border); })
        ];
        const auto Thickness = TAttribute<FOptionalSize>::CreateLambda([this] {
            return FOptionalSize(FMath::Max(0.f, Style.Stroke));
        });
        if (bVertical)
        {
            Box->SetWidthOverride(Thickness);
        }
        else
        {
            Box->SetHeightOverride(Thickness);
        }
        return Box;
    };
    return SNew(SOverlay)
        + SOverlay::Slot()[Surface.ToSharedRef()]
        + SOverlay::Slot().VAlign(VAlign_Top)[Edge(false)]
        + SOverlay::Slot().VAlign(VAlign_Bottom)[Edge(false)]
        + SOverlay::Slot().HAlign(HAlign_Left)[Edge(true)]
        + SOverlay::Slot().HAlign(HAlign_Right)[Edge(true)];
}

TSharedRef<SWidget> UCFTile::BuildTileContent()
{
    return GetContent() ? GetContent()->TakeWidget() : SNullWidget::NullWidget;
}

void UCFTile::OnSlotAdded(UPanelSlot*)
{
    if (Surface)
    {
        Surface->SetContent(BuildTileContent());
    }
}

void UCFTile::OnSlotRemoved(UPanelSlot*)
{
    if (Surface)
    {
        Surface->SetContent(SNullWidget::NullWidget);
    }
}

void UCFTile::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);
    Surface.Reset();
}
