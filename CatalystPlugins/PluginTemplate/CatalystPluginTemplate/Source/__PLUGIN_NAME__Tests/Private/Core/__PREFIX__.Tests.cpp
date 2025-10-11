#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(__PLUGIN_DISPLAY_NAME__Tests_SetGetString,
    "__PREFIX__.__PLUGIN_DISPLAY_NAME__.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool __PLUGIN_DISPLAY_NAME__Tests_SetGetString::RunTest(const FString& Parameters)
{
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
