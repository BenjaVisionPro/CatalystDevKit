#include "Misc/AutomationTest.h"
#include "SubSystem/CFSubsystem.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_Subsystem_Get_NullWorld_ReturnsNull,
    "CF.Subsystem.Get.WithoutWorld.ReturnsNull",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_Subsystem_Get_NullWorld_ReturnsNull::RunTest(const FString& Parameters)
{
    UCFSubsystem* S = UCFSubsystem::Get(nullptr);
    TestNull(TEXT("Get(nullptr) should return null"), S);
    return true;
}