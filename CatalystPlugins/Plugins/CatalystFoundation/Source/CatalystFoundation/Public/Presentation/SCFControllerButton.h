#pragma once

#include "InputCoreTypes.h"
#include "Presentation/CFControllerHold.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SLeafWidget.h"

class ULocalPlayer;

enum class ECFControllerPlatform : uint8
{
    Keyboard,
    Xbox,
    PlayStation
};

struct FCFControllerButtonStyle
{
    FSlateFontInfo LabelFont;
    FSlateFontInfo GlyphFont;
    FLinearColor LabelTint = FLinearColor::White;
    FLinearColor CapTint = FLinearColor(1.f, 1.f, 1.f, .65f);
    FLinearColor GlyphTint = FLinearColor::Black;
    float DisabledOpacity = .35f;
};

/** A platform-aware action prompt with tap or target-bound hold activation. */
class CATALYSTFOUNDATION_API SCFControllerButton final : public SLeafWidget
{
public:
    SLATE_BEGIN_ARGS(SCFControllerButton)
        : _Label(FText::GetEmpty()), _Available(true), _Player(nullptr), _HoldMilliseconds(0) {}
        SLATE_ATTRIBUTE(FText, Label)
        SLATE_ATTRIBUTE(ECFControllerPlatform, Platform)
        SLATE_ATTRIBUTE(bool, Available)
        SLATE_ATTRIBUTE(FGuid, Target)
        SLATE_ARGUMENT(FKey, KeyboardKey)
        SLATE_ARGUMENT(FKey, ControllerKey)
        SLATE_ARGUMENT(ULocalPlayer*, Player)
        SLATE_ARGUMENT(int32, HoldMilliseconds)
        SLATE_ARGUMENT(FCFControllerButtonStyle, Style)
        SLATE_EVENT(FSimpleDelegate, OnActivated)
    SLATE_END_ARGS()

    void Construct(const FArguments& Args);

    static ECFControllerPlatform PlatformForPlayer(const ULocalPlayer& Player);
    static FText GlyphFor(const FKey& Key, ECFControllerPlatform Platform);
    static FVector2D Measure(const FText& Label, const FKey& Key, ECFControllerPlatform Platform,
        const FCFControllerButtonStyle& Style, bool bRequiresHold = false);
    static int32 Draw(const FGeometry& Geometry, FSlateWindowElementList& Elements, int32 Layer,
        const FVector2D& Origin, const FText& Label, const FKey& Key, ECFControllerPlatform Platform,
        const FCFControllerButtonStyle& Style, bool bAvailable, bool bRequiresHold = false,
        const FCFControllerHoldIndicator& Indicator = {});

    virtual bool SupportsKeyboardFocus() const override { return true; }
    virtual FVector2D ComputeDesiredSize(float) const override;
    virtual FReply OnKeyDown(const FGeometry&, const FKeyEvent& Event) override;
    virtual FReply OnKeyUp(const FGeometry&, const FKeyEvent& Event) override;
    virtual FReply OnMouseButtonDown(const FGeometry&, const FPointerEvent& Event) override;
    virtual FReply OnMouseButtonUp(const FGeometry& Geometry, const FPointerEvent& Event) override;
    virtual void OnMouseCaptureLost(const FCaptureLostEvent&) override;
    virtual void OnFocusLost(const FFocusEvent&) override;
    virtual int32 OnPaint(const FPaintArgs&, const FGeometry&, const FSlateRect&, FSlateWindowElementList&,
        int32, const FWidgetStyle&, bool) const override;

private:
    const FKey& GetKey() const;
    ECFControllerPlatform GetPlatform() const;
    void UpdateHold();
    void BeginHold();
    EActiveTimerReturnType TickHold(double, float);
    void Release();

    TAttribute<FText> Label;
    TAttribute<ECFControllerPlatform> Platform;
    TAttribute<bool> Available;
    TAttribute<FGuid> Target;
    TWeakObjectPtr<ULocalPlayer> Player;
    FKey KeyboardKey;
    FKey ControllerKey;
    FKey DownKey;
    FCFControllerButtonStyle Style;
    FSimpleDelegate OnActivated;
    TOptional<FCFControllerHold> Hold;
    FGuid ButtonTarget;
    bool bHoldTimerActive = false;
};
