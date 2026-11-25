#pragma once

#include "Components/ContentWidget.h"
#include "CFTile.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFTileStyle
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FLinearColor Background = FLinearColor(0.02f, 0.025f, 0.03f, 0.8f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FLinearColor FocusedBackground = FLinearColor(0.12f, 0.16f, 0.20f, 0.9f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FLinearColor Border = FLinearColor(1.f, 1.f, 1.f, 0.35f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (ClampMin = "0.0"))
    float Stroke = 1.f;
};

/** Themeable frame shared by native and Widget Blueprint content. */
UCLASS(BlueprintType, Blueprintable)
class CATALYSTFOUNDATION_API UCFTile : public UContentWidget
{
    GENERATED_BODY()

public:
    UCFTile();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FCFTileStyle Style;

    UFUNCTION(BlueprintCallable, Category = "Tile")
    void SetVisualState(float InFocusProgress, float InOpacity);

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual TSharedRef<SWidget> BuildTileContent();
    virtual void OnSlotAdded(UPanelSlot* Slot) override;
    virtual void OnSlotRemoved(UPanelSlot* Slot) override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
    TSharedPtr<class SBorder> Surface;
    float FocusProgress = 0.f;
};
