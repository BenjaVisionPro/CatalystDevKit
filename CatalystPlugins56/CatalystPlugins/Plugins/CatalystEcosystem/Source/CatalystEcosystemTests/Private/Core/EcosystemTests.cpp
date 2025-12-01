#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(EcosystemTests_SetGetString,
    "CE.Ecosystems.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool EcosystemTests_SetGetString::RunTest(const FString& Parameters)
{
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
