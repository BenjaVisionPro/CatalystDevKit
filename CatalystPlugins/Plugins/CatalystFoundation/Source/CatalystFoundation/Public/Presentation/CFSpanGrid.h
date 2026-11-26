#pragma once

#include "Components/ScrollBox.h"
#include "CFSpanGrid.generated.h"

class UHorizontalBox;
class UHorizontalBoxSlot;

/** Packs widgets into equal-width columns in insertion order. */
UCLASS(BlueprintType)
class CATALYSTFOUNDATION_API UCFSpanGrid : public UScrollBox
{
    GENERATED_BODY()

public:
    void Configure(int32 InColumns, float InRowHeight, float InGap, float InRowGap, float InGroupGap,
        float InHeadingHeight,
        const FMargin& InHeadingPadding, const FSlateFontInfo& InHeadingFont, FLinearColor InHeadingTint);
    void AddHeading(const FText& Label);
    void AddItem(UWidget& Item, int32 ColumnSpan);

    /** Distribute the available height across rows after reserving headings and gaps. */
    void SetFillPanelHeight(bool bEnabled) { bFillPanelHeight = bEnabled; }
    void FitLastRowBottom(double Bottom);

    /** Arrange the row in the output space, then map its edges back to the grid's layout space. */
    void ApplyHorizontalProjection(double OutputWidth, TFunctionRef<double(double)> ToLayoutX);

    int32 GetColumnCount() const { return Columns; }

private:
    double GetLastRowBottom() const;

    UPROPERTY(Transient)
    TObjectPtr<UHorizontalBox> Row;

    UPROPERTY(Transient)
    TObjectPtr<UHorizontalBoxSlot> Remainder;

    TMap<UHorizontalBox*, TArray<int32>> RowSpans;
    FMargin HeadingPadding;
    FSlateFontInfo HeadingFont;
    FLinearColor HeadingTint;
    int32 Columns = 1;
    int32 UsedColumns = 0;
    float RowHeight = 0.f;
    float HeadingHeight = 0.f;
    float Gap = 0.f;
    float RowGap = 0.f;
    float GroupGap = 0.f;
    double LastFittedBottom = 0.0;
    bool bFillPanelHeight = false;
};
