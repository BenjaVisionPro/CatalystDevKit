#include "Misc/AutomationTest.h"
#include "Model/CFObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCFObjectIdentityTest,
    "Catalyst.Foundation.Object.Identity",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCFObjectIdentityTest::RunTest(const FString&)
{
    const FCFIdentifiableObject Supplied(TEXT("example:ExistingIdentifier"));
    TestEqual(TEXT("Keep the supplied identifier"), Supplied.Identifier, FString(TEXT("example:ExistingIdentifier")));
    const FCFLabelledObject Labelled;
    FGuid Generated;
    TestTrue(TEXT("Local objects receive a UUID"), FGuid::Parse(Labelled.Identifier, Generated));
    TestEqual(TEXT("The base icon matches GT"), Labelled.Icon, FName(TEXT("circleQuestion")));
    TestTrue(TEXT("The label is available on the labelled subclass"), Labelled.Label.IsEmpty());
    return true;
}
