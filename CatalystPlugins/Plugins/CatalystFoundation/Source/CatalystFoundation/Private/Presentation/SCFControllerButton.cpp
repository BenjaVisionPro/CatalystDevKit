#include "Presentation/SCFControllerButton.h"

#include "Brushes/SlateRoundedBoxBrush.h"
#include "Engine/LocalPlayer.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GenericPlatform/InputDeviceRegistry.h"
#include "HAL/PlatformTime.h"
#include "Rendering/DrawElements.h"
#include "Rendering/SlateRenderer.h"
#include "Styling/CoreStyle.h"

namespace
{
bool IsShoulder(const FKey& Key)
{
    return Key == EKeys::Gamepad_LeftShoulder || Key == EKeys::Gamepad_RightShoulder
        || Key == EKeys::Gamepad_LeftTrigger || Key == EKeys::Gamepad_RightTrigger;
}

FVector2D CapExtent(const FKey& Key)
{
    return IsShoulder(Key) ? FVector2D(23, 18) : FVector2D(21, 21);
}

FText DisplayLabel(const FText& Label, const FText& Glyph, ECFControllerPlatform Platform, bool bRequiresHold)
{
    return Platform == ECFControllerPlatform::Keyboard && !bRequiresHold && !Label.IsEmpty()
        ? FText::Format(NSLOCTEXT("CFControllerButton", "KeyboardAction", "{0}  {1}"), Glyph, Label) : Label;
}

void DrawHold(const FGeometry& Geometry, FSlateWindowElementList& Elements, int32 Layer,
    FVector2D Center, FLinearColor Tint, const FCFControllerHoldIndicator& Indicator)
{
    constexpr int32 Steps = 12;
    constexpr double Span = 2.0 * PI / FCFControllerHoldIndicator::Segments;
    for (int32 Segment = 0; Segment < FCFControllerHoldIndicator::Segments; ++Segment)
    {
        const double Middle = -PI * .5 + Segment * Span;
        const bool bLit = Segment < Indicator.Completed
            || (Segment == Indicator.Completed && Indicator.bFlashOn);
        TArray<FVector2D> Arc;
        Arc.Reserve(Steps + 1);
        for (int32 Step = 0; Step <= Steps; ++Step)
        {
            const double Angle = Middle + (double(Step) / Steps - .5) * Span * .88;
            Arc.Add(Center + FVector2D(FMath::Cos(Angle), FMath::Sin(Angle)) * 12.4);
        }
        FSlateDrawElement::MakeLines(Elements, Layer, Geometry.ToPaintGeometry(), Arc,
            ESlateDrawEffect::NoPixelSnapping, bLit ? Tint : Tint.CopyWithNewOpacity(Tint.A * .42f), true, 3.3f);
    }
}
}

void SCFControllerButton::Construct(const FArguments& Args)
{
    Label = Args._Label;
    Platform = Args._Platform;
    Available = Args._Available;
    Target = Args._Target;
    Player = Args._Player;
    KeyboardKey = Args._KeyboardKey;
    ControllerKey = Args._ControllerKey;
    Style = Args._Style;
    if (!Style.LabelFont.HasValidFont())
    {
        Style.LabelFont = FCoreStyle::GetDefaultFontStyle("Regular", 15);
    }
    if (!Style.GlyphFont.HasValidFont())
    {
        Style.GlyphFont = FCoreStyle::GetDefaultFontStyle("Regular", 10);
    }
    OnActivated = Args._OnActivated;
    if (Args._HoldMilliseconds > 0)
    {
        Hold.Emplace(Args._HoldMilliseconds);
        ButtonTarget = FGuid::NewGuid();
    }
}

ECFControllerPlatform SCFControllerButton::PlatformForPlayer(const ULocalPlayer& Player)
{
    const auto* Devices = UInputDeviceSubsystem::Get();
    if (!Devices)
    {
        return ECFControllerPlatform::Keyboard;
    }
    const auto User = Player.GetPlatformUserId();
    const auto Hardware = Devices->GetMostRecentlyUsedHardwareDevice(User);
    if (Hardware.PrimaryDeviceType != EHardwareDevicePrimaryType::Gamepad)
    {
        return ECFControllerPlatform::Keyboard;
    }
    const auto Descriptor = FInputDeviceRegistry::FindDescriptor(Devices->GetMostRecentlyUsedInputDeviceId(User));
    const FString Name = Descriptor.IsSet() ? Descriptor->InputDeviceName.ToString()
        : Hardware.InputClassName.ToString() + TEXT(" ") + Hardware.HardwareDeviceIdentifier.ToString();
    return Name.Contains(TEXT("DualSense")) || Name.Contains(TEXT("DualShock")) || Name.Contains(TEXT("PlayStation"))
        || Name.Contains(TEXT("PS5")) || Name.Contains(TEXT("PS4"))
        ? ECFControllerPlatform::PlayStation : ECFControllerPlatform::Xbox;
}

FText SCFControllerButton::GlyphFor(const FKey& Key, ECFControllerPlatform Platform)
{
    if (Platform == ECFControllerPlatform::Keyboard)
    {
        return Key.GetDisplayName();
    }
    const bool bPS = Platform == ECFControllerPlatform::PlayStation;
    const struct { FKey Key; const TCHAR* PlayStation; const TCHAR* Xbox; } Glyphs[] = {
        {EKeys::Gamepad_FaceButton_Bottom, TEXT("×"), TEXT("A")},
        {EKeys::Gamepad_FaceButton_Right, TEXT("○"), TEXT("B")},
        {EKeys::Gamepad_FaceButton_Left, TEXT("□"), TEXT("X")},
        {EKeys::Gamepad_FaceButton_Top, TEXT("△"), TEXT("Y")},
        {EKeys::Gamepad_LeftShoulder, TEXT("L1"), TEXT("LB")},
        {EKeys::Gamepad_RightShoulder, TEXT("R1"), TEXT("RB")},
        {EKeys::Gamepad_LeftTrigger, TEXT("L2"), TEXT("LT")},
        {EKeys::Gamepad_RightTrigger, TEXT("R2"), TEXT("RT")},
        {EKeys::Gamepad_LeftThumbstick, TEXT("L3"), TEXT("LS")},
        {EKeys::Gamepad_RightThumbstick, TEXT("R3"), TEXT("RS")}
    };
    for (const auto& Entry : Glyphs)
    {
        if (Entry.Key == Key)
        {
            return FText::FromString(bPS ? Entry.PlayStation : Entry.Xbox);
        }
    }
    return Key.GetDisplayName();
}

FVector2D SCFControllerButton::Measure(const FText& Label, const FKey& Key, ECFControllerPlatform Platform,
    const FCFControllerButtonStyle& Style, bool bRequiresHold)
{
    const FText Text = DisplayLabel(Label, GlyphFor(Key, Platform), Platform, bRequiresHold);
    FVector2D Size = FSlateApplication::Get().GetRenderer()->GetFontMeasureService()->Measure(Text, Style.LabelFont);
    if (Platform != ECFControllerPlatform::Keyboard || bRequiresHold || Label.IsEmpty())
    {
        const auto CapSize = CapExtent(Key);
        Size.X += CapSize.X + (Label.IsEmpty() ? (bRequiresHold ? 7.0 : 0.0) : (bRequiresHold ? 9.0 : 5.0));
        Size.Y = FMath::Max(Size.Y, bRequiresHold ? 32.0 : CapSize.Y);
    }
    return Size;
}

int32 SCFControllerButton::Draw(const FGeometry& Geometry, FSlateWindowElementList& Elements, int32 Layer,
    const FVector2D& Origin, const FText& Label, const FKey& Key, ECFControllerPlatform Platform,
    const FCFControllerButtonStyle& Style, bool bAvailable, bool bRequiresHold, const FCFControllerHoldIndicator& Indicator)
{
    const FText Glyph = GlyphFor(Key, Platform);
    const FText Text = DisplayLabel(Label, Glyph, Platform, bRequiresHold);
    const auto FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    const FVector2D TextSize = FontMeasure->Measure(Text, Style.LabelFont);
    const float Opacity = bAvailable ? 1.f : Style.DisabledOpacity;
    const auto DrawText = [&](const FText& Value, const FSlateFontInfo& Font,
        const FVector2D& Position, const FVector2D& Size, FLinearColor Tint)
    {
        Tint.A *= Opacity;
        FSlateDrawElement::MakeText(Elements, Layer + 1, Geometry.ToPaintGeometry(Size, FSlateLayoutTransform(Position)),
            Value, Font, ESlateDrawEffect::NoPixelSnapping, Tint);
    };

    FVector2D TextOrigin = Origin;
    if (Platform != ECFControllerPlatform::Keyboard || bRequiresHold || Label.IsEmpty())
    {
        const FVector2D CapSize = CapExtent(Key);
        const double CapY = Label.IsEmpty() ? 0.0 : (TextSize.Y - CapSize.Y) * .5;
        const FVector2D CapOrigin = Origin + FVector2D(bRequiresHold ? 3.5 : 0.0, CapY);
        static const FSlateRoundedBoxBrush RoundCap(FLinearColor::White, 10.5f);
        static const FSlateRoundedBoxBrush ShoulderCap(FLinearColor::White, 4.f);
        FLinearColor Fill = Style.CapTint.CopyWithNewOpacity(Style.CapTint.A * Opacity);
        FSlateDrawElement::MakeBox(Elements, Layer,
            Geometry.ToPaintGeometry(CapSize, FSlateLayoutTransform(CapOrigin)),
            IsShoulder(Key) ? &ShoulderCap : &RoundCap, ESlateDrawEffect::NoPixelSnapping, Fill);
        const auto& Font = Glyph.ToString().Len() == 1 && !IsShoulder(Key) ? Style.LabelFont : Style.GlyphFont;
        const FVector2D GlyphSize = FontMeasure->Measure(Glyph, Font);
        DrawText(Glyph, Font, CapOrigin + (CapSize - GlyphSize) * .5, GlyphSize, Style.GlyphTint);
        if (bRequiresHold)
        {
            DrawHold(Geometry, Elements, Layer + 2, CapOrigin + CapSize * .5, Fill, Indicator);
        }
        TextOrigin.X += CapSize.X + (bRequiresHold ? 9.0 : 5.0);
    }
    DrawText(Text, Style.LabelFont, TextOrigin, TextSize, Style.LabelTint);
    return Layer + 2;
}

const FKey& SCFControllerButton::GetKey() const
{
    return GetPlatform() == ECFControllerPlatform::Keyboard ? KeyboardKey : ControllerKey;
}

ECFControllerPlatform SCFControllerButton::GetPlatform() const
{
    if (Platform.IsSet())
    {
        return Platform.Get();
    }
    const auto* Owner = Player.Get();
    return Owner ? PlatformForPlayer(*Owner) : ECFControllerPlatform::Xbox;
}

FVector2D SCFControllerButton::ComputeDesiredSize(float) const
{
    return Measure(Label.Get(), GetKey(), GetPlatform(), Style, Hold.IsSet());
}

int32 SCFControllerButton::OnPaint(const FPaintArgs&, const FGeometry& Geometry, const FSlateRect&,
    FSlateWindowElementList& Elements, int32 Layer, const FWidgetStyle&, bool bParentEnabled) const
{
    return Draw(Geometry, Elements, Layer, FVector2D(0, Hold ? 6.f : 0.f), Label.Get(), GetKey(), GetPlatform(), Style,
        bParentEnabled && IsEnabled() && Available.Get(), Hold.IsSet(),
        Hold ? Hold->GetIndicator(FPlatformTime::Seconds()) : FCFControllerHoldIndicator{});
}

void SCFControllerButton::UpdateHold()
{
    if (Hold && Hold->Update(DownKey.IsValid(), IsEnabled() && Available.Get() ? Target.Get(ButtonTarget) : FGuid(),
        FPlatformTime::Seconds()))
    {
        OnActivated.ExecuteIfBound();
    }
}

void SCFControllerButton::BeginHold()
{
    if (!Hold)
    {
        return;
    }
    UpdateHold();
    if (!bHoldTimerActive)
    {
        bHoldTimerActive = true;
        RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SCFControllerButton::TickHold));
    }
}

EActiveTimerReturnType SCFControllerButton::TickHold(double, float)
{
    UpdateHold();
    Invalidate(EInvalidateWidgetReason::Paint);
    bHoldTimerActive = DownKey.IsValid() || Hold->GetIndicator(FPlatformTime::Seconds()).bAnimating;
    return bHoldTimerActive ? EActiveTimerReturnType::Continue : EActiveTimerReturnType::Stop;
}

FReply SCFControllerButton::OnKeyDown(const FGeometry&, const FKeyEvent& Event)
{
    if (!IsEnabled() || !Available.Get() || (Event.GetKey() != KeyboardKey && Event.GetKey() != ControllerKey))
    {
        return FReply::Unhandled();
    }
    if (!Event.IsRepeat() && !DownKey.IsValid())
    {
        DownKey = Event.GetKey();
        if (Hold)
        {
            BeginHold();
        }
        else
        {
            OnActivated.ExecuteIfBound();
        }
    }
    return FReply::Handled();
}

FReply SCFControllerButton::OnKeyUp(const FGeometry&, const FKeyEvent& Event)
{
    if (Event.GetKey() != DownKey)
    {
        return FReply::Unhandled();
    }
    Release();
    return FReply::Handled();
}

FReply SCFControllerButton::OnMouseButtonDown(const FGeometry&, const FPointerEvent& Event)
{
    if (!IsEnabled() || !Available.Get() || DownKey.IsValid() || Event.GetEffectingButton() != EKeys::LeftMouseButton)
    {
        return FReply::Unhandled();
    }
    DownKey = EKeys::LeftMouseButton;
    BeginHold();
    return FReply::Handled().SetUserFocus(SharedThis(this), EFocusCause::Mouse).CaptureMouse(SharedThis(this));
}

FReply SCFControllerButton::OnMouseButtonUp(const FGeometry& Geometry, const FPointerEvent& Event)
{
    if (DownKey != EKeys::LeftMouseButton || Event.GetEffectingButton() != DownKey)
    {
        return FReply::Unhandled();
    }
    Release();
    if (!Hold && IsEnabled() && Available.Get() && Geometry.IsUnderLocation(Event.GetScreenSpacePosition()))
    {
        OnActivated.ExecuteIfBound();
    }
    return FReply::Handled().ReleaseMouseCapture();
}

void SCFControllerButton::Release()
{
    DownKey = FKey();
    UpdateHold();
    Invalidate(EInvalidateWidgetReason::Paint);
}

void SCFControllerButton::OnMouseCaptureLost(const FCaptureLostEvent&)
{
    Release();
}

void SCFControllerButton::OnFocusLost(const FFocusEvent&)
{
    Release();
}
