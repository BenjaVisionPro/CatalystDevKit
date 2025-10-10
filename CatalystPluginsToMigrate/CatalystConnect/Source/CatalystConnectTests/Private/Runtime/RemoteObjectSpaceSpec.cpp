#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Runtime/UBVCRemoteObjectSpace.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCObjectSpace_SubscribeUnsubscribe,
    "BVC.ObjectSpace.SubscribeUnsubscribe",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCObjectSpace_SubscribeUnsubscribe::RunTest(const FString& Parameters)
{
    UBVCRemoteObjectSpace* Space = NewObject<UBVCRemoteObjectSpace>();

    FBVCSubscriptionHandle H = Space->Subscribe({TEXT("Player"), TEXT("ChatMessage")}, TEXT("Global"), true);
    TestTrue(TEXT("Valid SubId"), H.SubId > 0);

    Space->Unsubscribe(H);
    Space->Unsubscribe(H); // idempotent

    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
