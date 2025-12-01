#include "Misc/AutomationTest.h"
#include "Model/CFModelAsset.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_ModelAsset_ApplyJsonString_Invalid_ReturnsFalseAndError,
    "CF.ModelAsset.ApplyJsonString.InvalidJson",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_ModelAsset_ApplyJsonString_Invalid_ReturnsFalseAndError::RunTest(const FString& Parameters)
{
    UCFModelAsset* M = NewObject<UCFModelAsset>();
    if (!TestNotNull(TEXT("Model asset constructed"), M)) return false;

    FString Err;
    const bool bOK = M->ApplyJsonString(TEXT("{ not-json"), Err);
    TestFalse(TEXT("Invalid JSON should fail"), bOK);
    TestTrue(TEXT("Error message populated"), Err.Len() > 0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_ModelAsset_ApplyJsonString_Empty_NoCrash,
    "CF.ModelAsset.ApplyJsonString.EmptyJson.NoCrash",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_ModelAsset_ApplyJsonString_Empty_NoCrash::RunTest(const FString& Parameters)
{
    UCFModelAsset* M = NewObject<UCFModelAsset>();
    if (!TestNotNull(TEXT("Model asset constructed"), M)) return false;

    FString Err;
    const bool bOK = M->ApplyJsonString(TEXT("{}"), Err);

    // We don’t assume schema access; just require no crash.
    if (!bOK)
    {
        TestTrue(TEXT("Error message provided on failure"), Err.Len() > 0);
    }
    TestTrue(TEXT("Function completed without crash"), true);
    return true;
}