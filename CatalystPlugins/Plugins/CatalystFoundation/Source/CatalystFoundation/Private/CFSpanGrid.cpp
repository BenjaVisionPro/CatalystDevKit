#include "Presentation/CFSpanGrid.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"

void UCFSpanGrid::Configure(int32 InColumns, float InRowHeight, float InGap, float InRowGap, float InGroupGap,
    float InHeadingHeight, const FMargin& InHeadingPadding, const FSlateFontInfo& InHeadingFont, FLinearColor InHeadingTint)
{
    RowSpans.Reset();
    ClearChildren();
    Row = nullptr;
    Remainder = nullptr;
    UsedColumns = 0;
    Columns = FMath::Max(1, InColumns);
    RowHeight = InRowHeight;
    Gap = InGap;
    RowGap = InRowGap;
    GroupGap = InGroupGap;
    HeadingHeight = InHeadingHeight;
    HeadingPadding = InHeadingPadding;
    HeadingFont = InHeadingFont;
    HeadingTint = InHeadingTint;
}

void UCFSpanGrid::AddHeading(const FText& Label)
{
    if (!Label.IsEmpty())
    {
        if (Row)
        {
            auto* RowBox = Row->GetParent();
            CastChecked<UScrollBoxSlot>(RowBox->Slot)->SetPadding(FMargin(0.f, 0.f, 0.f, GroupGap));
        }
        auto* Heading = NewObject<UTextBlock>(this);
        Heading->SetText(Label);
        Heading->SetFont(HeadingFont);
        Heading->SetColorAndOpacity(FSlateColor(HeadingTint));
        auto* HeadingBox = NewObject<USizeBox>(this);
        HeadingBox->SetHeightOverride(HeadingHeight);
        HeadingBox->AddChild(Heading);
        CastChecked<UScrollBoxSlot>(AddChild(HeadingBox))->SetPadding(HeadingPadding);
    }
    Row = nullptr;
    Remainder = nullptr;
}

void UCFSpanGrid::AddItem(UWidget& Item, int32 ColumnSpan)
{
    const int32 Span = FMath::Clamp(ColumnSpan, 1, Columns);
    if (!Row || UsedColumns + Span > Columns)
    {
        Row = NewObject<UHorizontalBox>(this);
        RowSpans.Add(Row.Get());
        auto* RowBox = NewObject<USizeBox>(this);
        RowBox->SetHeightOverride(RowHeight);
        RowBox->AddChild(Row);
        CastChecked<UScrollBoxSlot>(AddChild(RowBox))->SetPadding(FMargin(0.f, 0.f, 0.f, RowGap));
        UsedColumns = 0;
        Remainder = nullptr;
    }

    if (Remainder)
    {
        Row->RemoveChild(Remainder->Content);
        Remainder = nullptr;
    }
    RowSpans.FindChecked(Row.Get()).Add(Span);
    auto* TileSlot = Row->AddChildToHorizontalBox(&Item);
    FSlateChildSize Size;
    Size.SizeRule = ESlateSizeRule::Fill;
    Size.Value = Span;
    TileSlot->SetSize(Size);
    TileSlot->SetPadding(FMargin(UsedColumns > 0 ? Gap * .5f : 0.f, 0.f,
        UsedColumns + Span < Columns ? Gap * .5f : 0.f, 0.f));

    UsedColumns += Span;
    if (UsedColumns < Columns)
    {
        Remainder = Row->AddChildToHorizontalBox(NewObject<USpacer>(this));
        Size.Value = Columns - UsedColumns;
        Remainder->SetSize(Size);
    }
}


void UCFSpanGrid::ApplyHorizontalProjection(double OutputWidth, TFunctionRef<double(double)> ToLayoutX)
{
    for (const auto& [Box, Spans] : RowSpans)
    {
        const int32 SlotCount = Box->GetChildrenCount();
        const double WidthForTiles = OutputWidth - (SlotCount - 1) * Gap;
        if (WidthForTiles <= 0.0)
        {
            continue;
        }

        const double ColumnWidth = WidthForTiles / Columns;
        double OutputLeft = 0.0;
        int32 RemainingColumns = Columns;
        for (int32 Index = 0; Index < SlotCount; ++Index)
        {
            const int32 Span = Spans.IsValidIndex(Index) ? Spans[Index] : RemainingColumns;
            RemainingColumns -= Span;
            const double OutputRight = OutputLeft + ColumnWidth * Span;
            const double AfterGap = Index + 1 < SlotCount ? OutputRight + Gap : OutputRight;
            const double Left = ToLayoutX(OutputLeft);
            const double Right = ToLayoutX(OutputRight);
            const double Next = ToLayoutX(AfterGap);

            auto* Slot = CastChecked<UHorizontalBoxSlot>(Box->GetChildAt(Index)->Slot);
            FSlateChildSize Size(ESlateSizeRule::Fill);
            Size.Value = Right - Left;
            Slot->SetSize(Size);
            Slot->SetPadding(FMargin(0.f, 0.f, Next - Right, 0.f));
            OutputLeft = AfterGap;
        }
    }
}
