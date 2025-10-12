#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LandformTests_SetGetString,
    "CL.Landform.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool LandformTests_SetGetString::RunTest(const FString& Parameters)
{
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
