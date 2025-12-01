#if WITH_EDITOR

#include "Misc/AutomationTest.h"
#include "Modules/ModuleManager.h"
#include "UObject/UObjectGlobals.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_Editor_ModuleLoads,
    "CF.Editor.ModuleLoads",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_Editor_ModuleLoads::RunTest(const FString& Parameters)
{
    const bool bLoaded = FModuleManager::Get().IsModuleLoaded("CatalystFoundationEditor");
    TestTrue(TEXT("CatalystFoundationEditor module should be loaded"), bLoaded);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_Editor_Commandlet_ClassExists_WithoutInclude,
    "CF.Editor.Commandlet.ClassExists",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_Editor_Commandlet_ClassExists_WithoutInclude::RunTest(const FString& Parameters)
{
    // Look up the class by name without relying on deprecated ANY_PACKAGE.
    UClass* Cls = FindFirstObjectSafe<UClass>(TEXT("/Script/CatalystFoundationEditor.CFGenerateModelAssetsCommandlet"));
    TestNotNull(TEXT("CFGenerateModelAssetsCommandlet class should be registered"), Cls);
    return true;
}

#endif // WITH_EDITOR