#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FoundationTests_SetGetString,
    "CF.Foundation.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FoundationTests_SetGetString::RunTest(const FString& Parameters)
{
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
