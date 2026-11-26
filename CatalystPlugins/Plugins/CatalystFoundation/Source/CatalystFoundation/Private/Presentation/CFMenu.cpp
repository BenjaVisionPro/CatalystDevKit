#include "Presentation/CFMenu.h"

#include "InputCoreTypes.h"
#include "Rendering/DrawElements.h"
#include "Rendering/SlateRenderer.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"

namespace
{
DECLARE_DELEGATE_RetVal_OneParam(bool, FCFMenuStep, int32);

class SCFMenuInput : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCFMenuInput) {}
        SLATE_DEFAULT_SLOT(FArguments, Content)
        SLATE_EVENT(FCFMenuStep, OnStep)
    SLATE_END_ARGS()

    void Construct(const FArguments& Args)
    {
        OnStep = Args._OnStep;
        ChildSlot[Args._Content.Widget];
    }

    virtual bool SupportsKeyboardFocus() const override { return true; }

    virtual FReply OnKeyDown(const FGeometry&, const FKeyEvent& Event) override
    {
        const auto Key = Event.GetKey();
        if (Key == EKeys::Gamepad_LeftShoulder || Key == EKeys::Gamepad_RightShoulder)
        {
            const int32 Direction = Key == EKeys::Gamepad_LeftShoulder ? -1 : 1;
            if (OnStep.IsBound() && OnStep.Execute(Direction))
            {
                return FReply::Handled();
            }
        }
        return FReply::Unhandled();
    }

private:
    FCFMenuStep OnStep;
};

class SCFShoulderKeycap : public SLeafWidget
{
public:
    SLATE_BEGIN_ARGS(SCFShoulderKeycap) : _Mirrored(false) {}
        SLATE_ATTRIBUTE(FLinearColor, Tint)
        SLATE_ARGUMENT(bool, Mirrored)
    SLATE_END_ARGS()

    void Construct(const FArguments& Args)
    {
        Tint = Args._Tint;
        bMirrored = Args._Mirrored;
        SetVisibility(EVisibility::HitTestInvisible);
    }

    virtual FVector2D ComputeDesiredSize(float) const override { return FVector2D::ZeroVector; }

    virtual int32 OnPaint(const FPaintArgs&, const FGeometry& Geometry, const FSlateRect&, FSlateWindowElementList& Elements,
        int32 Layer, const FWidgetStyle& WidgetStyle, bool) const override
    {
        const FVector2D Size = Geometry.GetLocalSize();
        const FColor Color = (Tint.Get(FLinearColor::White) * WidgetStyle.GetColorAndOpacityTint()).ToFColorSRGB();
        const FVector2f Outline[]{{0, .47f}, {.33f, 0}, {.91f, 0}, {1, .18f}, {1, 1}, {0, 1}};
        TArray<FSlateVertex> Vertices;
        for (const auto& Point : Outline)
        {
            const float X = bMirrored ? 1.f - Point.X : Point.X;
            Vertices.Add(FSlateVertex::Make(Geometry.GetAccumulatedRenderTransform(),
                FVector2f(X * Size.X, Point.Y * Size.Y), FVector2f(.5f, .5f), Color));
        }
        const TArray<SlateIndex> Indices{0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5};
        const auto* White = FCoreStyle::Get().GetBrush("WhiteBrush");
        const auto Resource = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*White);
        FSlateDrawElement::MakeCustomVerts(Elements, Layer, Resource, Vertices, Indices, nullptr, 0, 0);
        return Layer;
    }

private:
    TAttribute<FLinearColor> Tint;
    bool bMirrored = false;
};
}

UCFMenuTheme::UCFMenuTheme()
{
    LabelFont = FCoreStyle::GetDefaultFontStyle("Regular", 13);
    ShoulderFont = FCoreStyle::GetDefaultFontStyle("Regular", 13);
    ActionLabelFont = FCoreStyle::GetDefaultFontStyle("Regular", 15);
    ActionGlyphFont = FCoreStyle::GetDefaultFontStyle("Regular", 10);
    SelectedFill = FLinearColor::FromSRGBColor(FColor(74, 20, 140)).CopyWithNewOpacity(.58f);
}

UCFMenuItem::UCFMenuItem()
{
    Icon.DrawAs = ESlateBrushDrawType::NoDrawType;
}

void UCFMenuItem::SetLabel(const FText& InLabel)
{
    Label = InLabel;
    InvalidateLayoutAndVolatility();
}

void UCFMenuItem::SetIcon(const FSlateBrush& InIcon)
{
    Icon = InIcon;
    InvalidateLayoutAndVolatility();
}

bool UCFMenuItem::IsSelected() const
{
    const auto* Menu = Cast<UCFMenu>(GetParent());
    return Menu && Menu->GetSelectedItem() == this;
}

const UCFMenuTheme& UCFMenuItem::GetMenuTheme() const
{
    const auto* Menu = Cast<UCFMenu>(GetParent());
    return Menu ? Menu->GetMenuTheme() : *GetDefault<UCFMenuTheme>();
}

FReply UCFMenuItem::SelectFromPointer()
{
    auto* Menu = Cast<UCFMenu>(GetParent());
    return Menu && Menu->SelectItem(Menu->GetChildIndex(this)) ? FReply::Handled() : FReply::Unhandled();
}

TSharedRef<SWidget> UCFMenuItem::RebuildWidget()
{
    const auto* White = FCoreStyle::Get().GetBrush("WhiteBrush");
    const auto Ink = [this] { return FSlateColor(IsSelected() ? GetMenuTheme().SelectedInk : GetMenuTheme().Ink); };
    return SNew(SBox)
        .MinDesiredWidth_Lambda([this] { return FOptionalSize(GetMenuTheme().MinimumItemWidth); })
        .MinDesiredHeight_Lambda([this] { return FOptionalSize(GetMenuTheme().MinimumItemHeight); })
        [
            SNew(SButton)
            .ButtonStyle(FCoreStyle::Get(), "NoBorder")
            .ContentPadding(0)
            .IsFocusable(false)
            .OnClicked(FOnClicked::CreateUObject(this, &UCFMenuItem::SelectFromPointer))
            [
                SNew(SOverlay)
                + SOverlay::Slot()
                [
                    SNew(SBorder).BorderImage(White)
                    .BorderBackgroundColor_Lambda([this] { return IsSelected() ? GetMenuTheme().SelectedFill : GetMenuTheme().InactiveFill; })
                    .Padding_Lambda([this] { return GetMenuTheme().ItemPadding; })
                    .HAlign(HAlign_Center).VAlign(VAlign_Center)
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                        [
                            SNew(SBox)
                            .WidthOverride_Lambda([this] { return FOptionalSize(GetMenuTheme().IconSize); })
                            .HeightOverride_Lambda([this] { return FOptionalSize(GetMenuTheme().IconSize); })
                            .Visibility_Lambda([this] {
                                return Icon.DrawAs == ESlateBrushDrawType::NoDrawType
                                    ? EVisibility::Collapsed : EVisibility::HitTestInvisible;
                            })
                            [
                                SNew(SScaleBox).Stretch(EStretch::ScaleToFit).HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [SNew(SImage).Image_Lambda([this] { return &Icon; }).ColorAndOpacity_Lambda(Ink)]
                            ]
                        ]
                        + SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
                        .Padding(TAttribute<FMargin>::CreateLambda([this] {
                            return FMargin(0, Icon.DrawAs == ESlateBrushDrawType::NoDrawType ? 0.f : GetMenuTheme().IconLabelGap, 0, 0);
                        }))
                        [
                            SNew(STextBlock).Text_Lambda([this] { return Label; })
                            .Font_Lambda([this] { return GetMenuTheme().LabelFont; }).ColorAndOpacity_Lambda(Ink)
                        ]
                    ]
                ]
                + SOverlay::Slot().VAlign(VAlign_Bottom)
                [
                    SNew(SBox)
                    .Visibility_Lambda([this] { return IsSelected() ? EVisibility::HitTestInvisible : EVisibility::Collapsed; })
                    .HeightOverride_Lambda([this] { return FOptionalSize(GetMenuTheme().SelectionRuleThickness); })
                    [
                        SNew(SBorder).Padding(0).BorderImage(White)
                        .BorderBackgroundColor_Lambda([this] { return GetMenuTheme().SelectedFill.CopyWithNewOpacity(1.f); })
                    ]
                ]
            ]
        ];
}

const UCFMenuTheme& UCFMenu::GetMenuTheme() const
{
    return Theme ? *Theme : *GetDefault<UCFMenuTheme>();
}

int32 UCFMenu::GetSelectedIndex() const
{
    return SelectedItem.IsValid() ? GetChildIndex(SelectedItem.Get()) : INDEX_NONE;
}

UCFMenuItem* UCFMenu::SelectableItem(int32 Index) const
{
    auto* Item = Cast<UCFMenuItem>(GetChildAt(Index));
    if (Item && Item->GetIsEnabled())
    {
        const auto Visibility = Item->GetVisibility();
        if (Visibility != ESlateVisibility::Hidden && Visibility != ESlateVisibility::Collapsed)
        {
            return Item;
        }
    }
    return nullptr;
}

bool UCFMenu::SelectItem(int32 Index)
{
    UCFMenuItem* Item = SelectableItem(Index);
    if (!Item)
    {
        return false;
    }
    if (SelectedItem.Get() != Item)
    {
        SelectedItem = Item;
        InvalidateLayoutAndVolatility();
        OnSelectionChanged.Broadcast(Index, Item);
    }
    return true;
}

bool UCFMenu::StepSelection(int32 Direction)
{
    const int32 Count = GetChildrenCount();
    if (Count == 0 || Direction == 0)
    {
        return false;
    }

    const int32 Step = Direction > 0 ? 1 : Count - 1;
    int32 Index = GetSelectedIndex();
    if (Index == INDEX_NONE)
    {
        Index = Direction > 0 ? Count - 1 : 0;
    }
    for (int32 Attempt = 0; Attempt < Count; ++Attempt)
    {
        Index = (Index + Step) % Count;
        if (SelectItem(Index))
        {
            return true;
        }
    }
    return false;
}

void UCFMenu::RefreshItems()
{
    if (!Items)
    {
        return;
    }
    if (!SelectableItem(GetSelectedIndex()))
    {
        SelectedItem = SelectableItem(InitialSelectedIndex);
    }
    Items->ClearChildren();
    for (int32 Index = 0; Index < GetChildrenCount(); ++Index)
    {
        auto* Item = Cast<UCFMenuItem>(GetChildAt(Index));
        if (Item)
        {
            if (!SelectedItem.IsValid())
            {
                SelectedItem = SelectableItem(Index);
            }
            Items->AddSlot().AutoWidth()[Item->TakeWidget()];
        }
    }
    InvalidateLayoutAndVolatility();
}

TSharedRef<SWidget> UCFMenu::BuildPrompt(bool bPrevious)
{
    const auto Text = [this, bPrevious] { return bPrevious ? PreviousPrompt : NextPrompt; };
    return SNew(SBox)
        .MinDesiredWidth_Lambda([this] { return FOptionalSize(GetMenuTheme().ShoulderKeycapSize.X); })
        .MinDesiredHeight_Lambda([this] { return FOptionalSize(GetMenuTheme().ShoulderKeycapSize.Y); })
        .Visibility_Lambda([Text] { return Text().IsEmpty() ? EVisibility::Collapsed : EVisibility::HitTestInvisible; })
        [
            SNew(SOverlay)
            + SOverlay::Slot()
            [
                SNew(SCFShoulderKeycap).Mirrored(!bPrevious)
                .Tint_Lambda([this] { return GetMenuTheme().ShoulderFill; })
            ]
            + SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text_Lambda(Text).Font_Lambda([this] { return GetMenuTheme().ShoulderFont; })
                .ColorAndOpacity_Lambda([this] { return FSlateColor(GetMenuTheme().ShoulderInk); })
            ]
        ];
}

TSharedRef<SWidget> UCFMenu::RebuildWidget()
{
    SAssignNew(Items, SHorizontalBox);
    RefreshItems();
    const auto* White = FCoreStyle::Get().GetBrush("WhiteBrush");
    const auto Edge = [this, White](bool bVertical)
    {
        auto Box = SNew(SBox)
        [
            SNew(SBorder).Padding(0).BorderImage(White)
            .BorderBackgroundColor_Lambda([this] { return GetMenuTheme().Track; })
        ];
        const auto Thickness = TAttribute<FOptionalSize>::CreateLambda([this] {
            return FOptionalSize(GetMenuTheme().TrackThickness);
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
    return SNew(SCFMenuInput).OnStep(FCFMenuStep::CreateUObject(this, &UCFMenu::StepSelection))
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
            .Padding(TAttribute<FMargin>::CreateLambda([this] { return FMargin(0, 0, PreviousPrompt.IsEmpty() ? 0.f : GetMenuTheme().ShoulderGap, 0); }))
            [BuildPrompt(true)]
            + SHorizontalBox::Slot().AutoWidth()
            [
                SNew(SOverlay)
                + SOverlay::Slot().Padding(TAttribute<FMargin>::CreateLambda([this] { return FMargin(GetMenuTheme().TrackThickness); }))
                [Items.ToSharedRef()]
                + SOverlay::Slot().VAlign(VAlign_Top)[Edge(false)]
                + SOverlay::Slot().VAlign(VAlign_Bottom)[Edge(false)]
                + SOverlay::Slot().HAlign(HAlign_Left)[Edge(true)]
                + SOverlay::Slot().HAlign(HAlign_Right)[Edge(true)]
            ]
            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
            .Padding(TAttribute<FMargin>::CreateLambda([this] { return FMargin(NextPrompt.IsEmpty() ? 0.f : GetMenuTheme().ShoulderGap, 0, 0, 0); }))
            [BuildPrompt(false)]
        ];
}

void UCFMenu::OnSlotAdded(UPanelSlot*)
{
    RefreshItems();
}

void UCFMenu::OnSlotRemoved(UPanelSlot*)
{
    RefreshItems();
}

void UCFMenu::ReleaseSlateResources(bool bReleaseChildren)
{
    Items.Reset();
    Super::ReleaseSlateResources(bReleaseChildren);
}
