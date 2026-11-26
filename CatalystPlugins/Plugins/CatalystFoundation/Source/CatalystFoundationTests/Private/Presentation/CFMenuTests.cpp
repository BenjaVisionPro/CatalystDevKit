#if WITH_DEV_AUTOMATION_TESTS

#include "Presentation/CFMenu.h"
#include "InputCoreTypes.h"
#include "Misc/AutomationTest.h"
#include "UObject/StrongObjectPtr.h"
#include "Widgets/SWidget.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCFMenuTest, "CF.Foundation.Menu.LayoutAndNavigation",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCFMenuTest::RunTest(const FString&)
{
    TStrongObjectPtr<UCFMenu> Menu(NewObject<UCFMenu>());
    Menu->Theme = NewObject<UCFMenuTheme>(Menu.Get());
    Menu->InitialSelectedIndex = 1;

    auto* Short = NewObject<UCFMenuItem>(Menu.Get());
    Short->SetLabel(FText::FromString(TEXT("Gear")));
    auto* Long = NewObject<UCFMenuItem>(Menu.Get());
    Long->SetLabel(FText::FromString(TEXT("Resource Collections")));
    auto* Disabled = NewObject<UCFMenuItem>(Menu.Get());
    Disabled->SetIsEnabled(false);
    Menu->AddChild(Short);
    Menu->AddChild(Long);
    Menu->AddChild(Disabled);

    const auto Slate = Menu->TakeWidget();
    Slate->SlatePrepass(1.f);
    const float Minimum = Menu->Theme->MinimumItemWidth;
    const float ShortWidth = Short->TakeWidget()->GetDesiredSize().X;
    const float LongWidth = Long->TakeWidget()->GetDesiredSize().X;
    TestEqual(TEXT("Short tab uses theme minimum"), ShortWidth, Minimum);
    TestTrue(TEXT("Tab grows to its label"), LongWidth > ShortWidth);
    const float MenuWidth = Slate->GetDesiredSize().X;
    Long->SetLabel(FText::FromString(TEXT("Stats")));
    Slate->SlatePrepass(1.f);
    TestEqual(TEXT("Changing a label recomputes its tab width"), Long->TakeWidget()->GetDesiredSize().X, Minimum);
    TestTrue(TEXT("Menu takes its width from its children"), Slate->GetDesiredSize().X < MenuWidth);
    TestEqual(TEXT("The authored initial index is selected"), Menu->GetSelectedIndex(), 1);

    const auto PressShoulder = [&Slate](const FKey& Key)
    {
        return Slate->OnKeyDown(FGeometry(), FKeyEvent(Key, FModifierKeysState{}, 0, false, 0, 0)).IsEventHandled();
    };
    TestTrue(TEXT("R1 navigates"), PressShoulder(EKeys::Gamepad_RightShoulder));
    TestEqual(TEXT("R1 skips disabled items and wraps"), Menu->GetSelectedIndex(), 0);
    TestTrue(TEXT("Selection is visible for the active item"), Short->IsSelected());
    TestTrue(TEXT("L1 navigates"), PressShoulder(EKeys::Gamepad_LeftShoulder));
    TestEqual(TEXT("L1 wraps back"), Menu->GetSelectedIndex(), 1);
    TestFalse(TEXT("Disabled item cannot be selected"), Menu->SelectItem(2));
    Menu->RemoveChild(Long);
    TestEqual(TEXT("Removing the active item selects an available item"), Menu->GetSelectedIndex(), 0);
    TestFalse(TEXT("Zero direction leaves the selection alone"), Menu->StepSelection(0));
    return true;
}

#endif
