#include "Misc/AutomationTest.h"
#include "Validation/CFValidationTypes.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_Validation_MakeFillsFields,
    "CF.Validation.MakeFillsFields",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_Validation_MakeFillsFields::RunTest(const FString& Parameters)
{
    const ECFValidationSeverity Sev = ECFValidationSeverity::Warning;
    const FName Code("Unit.Test");
    const FText Summary = FText::FromString(TEXT("Hello"));
    const FText Detail  = FText::FromString(TEXT("World"));
    const FString Path  = TEXT("/Some/Path");
    const FText Fix     = FText::FromString(TEXT("Do a thing."));

    const FCFValidationMessage M = FCFValidationMessage::Make(Sev, Code, Summary, Detail, Path, Fix);

    TestEqual(TEXT("Severity"), M.Severity, Sev);
    TestEqual(TEXT("Code"),     M.Code,     Code);
    TestEqual(TEXT("Summary"),  M.Summary.ToString(), Summary.ToString());
    TestEqual(TEXT("Detail"),   M.Detail.ToString(),  Detail.ToString());
    TestEqual(TEXT("Path"),     M.Path,     Path);
    TestEqual(TEXT("FixHint"),  M.FixHint.ToString(), Fix.ToString());
    return true;
}