#include "Presentation/CFTile.h"

#include "Brushes/SlateRoundedBoxBrush.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SNullWidget.h"

namespace
{
class SCFTileFrame final : public SLeafWidget
{
public:
    SLATE_BEGIN_ARGS(SCFTileFrame) {}
        SLATE_ATTRIBUTE(FCFTileStyle, Style)
    SLATE_END_ARGS()

    void Construct(const FArguments& Args)
    {
        Style = Args._Style;
        SetVisibility(EVisibility::HitTestInvisible);
    }

    FVector2D ComputeDesiredSize(float) const override { return FVector2D::ZeroVector; }

    int32 OnPaint(const FPaintArgs&, const FGeometry& Geometry, const FSlateRect&, FSlateWindowElementList& Elements,
        int32 Layer, const FWidgetStyle& WidgetStyle, bool) const override
    {
        const auto TileStyle = Style.Get();
        if (TileStyle.Stroke > 0.f)
        {
            Brush.OutlineSettings.Width = TileStyle.Stroke;
            Brush.OutlineSettings.Color = TileStyle.Border * WidgetStyle.GetColorAndOpacityTint();
            FSlateDrawElement::MakeBox(Elements, Layer, Geometry.ToPaintGeometry(), &Brush,
                ESlateDrawEffect::NoPixelSnapping, FLinearColor::Transparent);
        }
        return Layer;
    }

private:
    TAttribute<FCFTileStyle> Style;
    mutable FSlateRoundedBoxBrush Brush{FLinearColor::Transparent, 0.f, FLinearColor::Transparent, 1.f};
};
}

UCFTile::UCFTile()
{
    SetClipping(EWidgetClipping::ClipToBounds);
}

const UCFTileTheme& UCFTile::GetTileTheme() const
{
    return Theme ? *Theme : *GetDefault<UCFTileTheme>();
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
            const auto& Style = GetTileTheme().Style;
            return FSlateColor(FMath::Lerp(Style.Background, Style.FocusedBackground, FocusProgress));
        })
        .Padding(0)
        [BuildTileContent()];

    return SNew(SOverlay)
        + SOverlay::Slot()
        [
            SNew(SBackgroundBlur).Padding(0)
            .BlurStrength_Lambda([this] { return FMath::Max(0.f, GetTileTheme().Style.BackdropBlur); })
            [Surface.ToSharedRef()]
        ]
        + SOverlay::Slot()
        [
            SNew(SCFTileFrame).Style_Lambda([this] { return GetTileTheme().Style; })
        ];
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
