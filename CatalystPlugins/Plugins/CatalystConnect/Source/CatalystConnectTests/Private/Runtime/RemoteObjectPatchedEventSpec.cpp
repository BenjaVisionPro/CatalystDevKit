#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Runtime/UBVCRemoteObject.h"
#include "Test/RemoteObjectPatchedProbe.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCRemoteObject_PatchedEventFires,
    "BVC.RemoteObject.PatchedEventFiresOnGameThread",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCRemoteObject_PatchedEventFires::RunTest(const FString& Parameters)
{
    UBVCRemoteObject* Obj = NewObject<UBVCRemoteObject>();
    Obj->Id = FGuid::NewGuid();

    URemoteObjectPatchedProbe* Probe = NewObject<URemoteObjectPatchedProbe>();
    Obj->OnRemotePatched.AddDynamic(Probe, &URemoteObjectPatchedProbe::OnPatched);

    // This should internally bounce to the game thread before broadcasting.
    Obj->SetStringField(TEXT("Title"), TEXT("Hello"));

    // Wait a moment for the async dispatch (if any).
    const double Start = FPlatformTime::Seconds();
    while (!Probe->bCalled && (FPlatformTime::Seconds() - Start) < 1.0)
    {
        FPlatformProcess::Sleep(0.01);
    }

    TestTrue(TEXT("Delegate should fire"), Probe->bCalled);
    TestTrue(TEXT("Should fire on the game thread"), Probe->bWasGameThread);
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS