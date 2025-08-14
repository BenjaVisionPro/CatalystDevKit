#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Runtime/UBVCValidationEngine.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCValidation_Required,
    "BVC.Validation.Required",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCValidation_Required::RunTest(const FString& Parameters)
{
    FBVCMAAttribute Title;
    Title.Name = TEXT("Title");
    Title.Kind = EBVCMAKind::Scalar;
    Title.ScalarType = EBVCMAScalarType::String;
    Title.bNullable = false;

    FBVCMADescription Desc;
    Desc.Name = TEXT("Doc");
    Desc.Attributes = { Title };

    UBVCValidationEngine* Engine = NewObject<UBVCValidationEngine>();

    TArray<FBVCValidationIssue> Issues;
    const bool bOkEmpty = Engine->ValidateField(Desc, TEXT("Title"), TEXT("   "), Issues);
    TestFalse(TEXT("Empty trimmed string should fail required"), bOkEmpty);
    TestTrue(TEXT("Should report at least one issue"), Issues.Num() > 0);

    Issues.Reset();
    const bool bOkValue = Engine->ValidateField(Desc, TEXT("Title"), TEXT("Hello"), Issues);
    TestTrue(TEXT("Non-empty string should pass required"), bOkValue);
    TestEqual(TEXT("No issues for valid value"), Issues.Num(), 0);

    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
