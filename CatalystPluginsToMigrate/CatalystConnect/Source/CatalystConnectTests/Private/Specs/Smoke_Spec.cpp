#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
                                 FCatalystConnectSmokeTest,
                                 "CatalystConnect.Smoke.Compiles",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCatalystConnectSmokeTest::RunTest(const FString& Parameters) {
    TestTrue("True is true", true); return true;
}
