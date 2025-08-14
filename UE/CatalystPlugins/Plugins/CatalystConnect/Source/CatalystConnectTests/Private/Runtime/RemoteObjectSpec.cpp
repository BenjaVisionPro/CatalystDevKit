#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Runtime/UBVCRemoteObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCRemoteObject_SetGetString,
    "BVC.RemoteObject.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCRemoteObject_SetGetString::RunTest(const FString& Parameters)
{
    UBVCRemoteObject* Obj = NewObject<UBVCRemoteObject>();
    Obj->Id = FGuid::NewGuid();

    // Set then get
    const bool bSet = Obj->SetStringField(TEXT("Title"), TEXT("Hi JJ"));
    TestTrue(TEXT("SetStringField should return true"), bSet);

    FString Out;
    const bool bGot = Obj->GetStringField(TEXT("Title"), Out);
    TestTrue(TEXT("GetStringField should succeed"), bGot);
    TestEqual(TEXT("Value round-trips"), Out, FString(TEXT("Hi JJ")));

    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
