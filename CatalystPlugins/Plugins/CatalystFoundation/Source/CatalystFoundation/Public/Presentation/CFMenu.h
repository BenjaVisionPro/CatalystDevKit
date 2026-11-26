#pragma once

#include "Components/PanelWidget.h"
#include "Engine/DataAsset.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateBrush.h"
#include "CFMenu.generated.h"

class UCFMenu;
class UCFMenuItem;

UCLASS(BlueprintType)
class CATALYSTFOUNDATION_API UCFMenuTheme : public UDataAsset
{
    GENERATED_BODY()

public:
    UCFMenuTheme();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    TMap<FName, FSlateBrush> Icons;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout", meta = (ClampMin = "0"))
    float MinimumItemWidth = 92.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout")
    FMargin ItemPadding = FMargin(9.f, 3.f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout", meta = (ClampMin = "0"))
    float MinimumItemHeight = 48.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout", meta = (ClampMin = "0"))
    float IconSize = 24.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout", meta = (ClampMin = "0"))
    float IconLabelGap = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout")
    FVector2D ShoulderKeycapSize = FVector2D(36.f, 24.f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Layout", meta = (ClampMin = "0"))
    float ShoulderGap = 7.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FSlateFontInfo LabelFont;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FSlateFontInfo ShoulderFont;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor Ink = FLinearColor(0.9f, 0.96f, 0.92f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor SelectedInk = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor InactiveFill = FLinearColor(0.f, 0.f, 0.f, .05f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor SelectedFill;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor Track = FLinearColor(1.f, 1.f, 1.f, .15f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance", meta = (ClampMin = "0"))
    float TrackThickness = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance", meta = (ClampMin = "0"))
    float SelectionRuleThickness = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor ShoulderFill = FLinearColor(1.f, 1.f, 1.f, .65f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu|Appearance")
    FLinearColor ShoulderInk = FLinearColor::Black;
};

/** Icon and label composed as one size-to-content tab. */
UCLASS(BlueprintType, Blueprintable)
class CATALYSTFOUNDATION_API UCFMenuItem : public UWidget
{
    GENERATED_BODY()

public:
    UCFMenuItem();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    FText Label;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    FSlateBrush Icon;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void SetLabel(const FText& InLabel);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void SetIcon(const FSlateBrush& InIcon);

    UFUNCTION(BlueprintPure, Category = "Menu")
    bool IsSelected() const;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

private:
    const UCFMenuTheme& GetMenuTheme() const;
    FReply SelectFromPointer();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCFMenuSelectionChanged, int32, Index, UCFMenuItem*, Item);

/** A horizontal menu authored with Menu Item children in UMG. */
UCLASS(BlueprintType, Blueprintable)
class CATALYSTFOUNDATION_API UCFMenu : public UPanelWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    TObjectPtr<UCFMenuTheme> Theme;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu", meta = (ClampMin = "0"))
    int32 InitialSelectedIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    FText PreviousPrompt = NSLOCTEXT("CatalystFoundationMenu", "Previous", "L1");

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
    FText NextPrompt = NSLOCTEXT("CatalystFoundationMenu", "Next", "R1");

    UPROPERTY(BlueprintAssignable, Category = "Menu")
    FCFMenuSelectionChanged OnSelectionChanged;

    UFUNCTION(BlueprintCallable, Category = "Menu")
    bool SelectItem(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    bool StepSelection(int32 Direction);

    UFUNCTION(BlueprintPure, Category = "Menu")
    int32 GetSelectedIndex() const;

    UFUNCTION(BlueprintPure, Category = "Menu")
    UCFMenuItem* GetSelectedItem() const { return SelectedItem.Get(); }

    const UCFMenuTheme& GetMenuTheme() const;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override;
    virtual void OnSlotAdded(UPanelSlot* InSlot) override;
    virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

private:
    UCFMenuItem* SelectableItem(int32 Index) const;
    void RefreshItems();
    TSharedRef<SWidget> BuildPrompt(bool bPrevious);

    TWeakObjectPtr<UCFMenuItem> SelectedItem;
    TSharedPtr<class SHorizontalBox> Items;
};
