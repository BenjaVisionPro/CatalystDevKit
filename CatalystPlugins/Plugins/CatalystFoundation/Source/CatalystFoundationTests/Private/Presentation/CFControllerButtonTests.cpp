#include "Presentation/SCFControllerButton.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCFControllerButtonTest, "Catalyst.Foundation.ControllerButton",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCFControllerButtonTest::RunTest(const FString&)
{
    TestEqual(TEXT("PlayStation shows the cross"),
        SCFControllerButton::GlyphFor(EKeys::Gamepad_FaceButton_Bottom, ECFControllerPlatform::PlayStation).ToString(),
        FString(TEXT("×")));
    TestEqual(TEXT("Xbox shows A"),
        SCFControllerButton::GlyphFor(EKeys::Gamepad_FaceButton_Bottom, ECFControllerPlatform::Xbox).ToString(),
        FString(TEXT("A")));
    TestTrue(TEXT("Keyboard uses the key display name"),
        SCFControllerButton::GlyphFor(EKeys::Enter, ECFControllerPlatform::Keyboard).EqualTo(EKeys::Enter.GetDisplayName()));

    const FGuid First(1, 0, 0, 0);
    const FGuid Second(2, 0, 0, 0);
    FCFControllerHold Hold(1000);
    TestFalse(TEXT("Press begins a hold without activating"), Hold.Update(true, First, 10.0));
    TestTrue(TEXT("The current segment starts lit"), Hold.GetIndicator(10.01).bFlashOn);
    TestFalse(TEXT("The current segment flashes off after 30 ms"), Hold.GetIndicator(10.04).bFlashOn);
    TestEqual(TEXT("Two segments complete after 400 ms"), Hold.GetIndicator(10.41).Completed, 2);
    TestFalse(TEXT("Changing selection cancels the hold"), Hold.Update(true, Second, 10.45));
    TestEqual(TEXT("Cancelling starts the unwind at the current segment"), Hold.GetIndicator(10.46).Completed, 3);
    TestEqual(TEXT("Unwind loses one segment every 50 ms"), Hold.GetIndicator(10.51).Completed, 2);
    TestFalse(TEXT("The held button cannot start again on another target"), Hold.Update(true, Second, 11.5));
    Hold.Update(false, Second, 11.51);
    Hold.Update(true, Second, 12.0);
    TestFalse(TEXT("The action cannot activate before one second"), Hold.Update(true, Second, 12.99));
    TestTrue(TEXT("The action activates at one second"), Hold.Update(true, Second, 13.0));
    TestEqual(TEXT("Confirmation starts with the ring off"), Hold.GetIndicator(13.01).Completed, 0);
    TestEqual(TEXT("Confirmation flashes the full ring"), Hold.GetIndicator(13.07).Completed, FCFControllerHoldIndicator::Segments);
    TestFalse(TEXT("Continuing to hold does not activate twice"), Hold.Update(true, Second, 13.4));

    auto Button = SNew(SCFControllerButton).KeyboardKey(EKeys::Enter).Available(false);
    const auto Geometry = FGeometry::MakeRoot(FVector2D(100, 28), FSlateLayoutTransform());
    TestFalse(TEXT("A disabled widget does not accept the activation key"),
        Button->OnKeyDown(Geometry, FKeyEvent(EKeys::Enter, FModifierKeysState(), 0, false, 0, 0)).IsEventHandled());
    return true;
}
#endif
