#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Schema/UBVCSchemaRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCSchemaRegistry_FindByName,
    "BVC.SchemaRegistry.FindByName",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCSchemaRegistry_FindByName::RunTest(const FString& Parameters)
{
    FBVCMADescription D; D.Name = TEXT("Player"); D.Version = 1;
    FBVCMADescriptionContainer C;
    C.CatalogId = FGuid::NewGuid();
    C.Hash = TEXT("test");
    C.Descriptions = { D };

    UBVCSchemaRegistry* Reg = NewObject<UBVCSchemaRegistry>();
    Reg->RegisterCatalog(C);

    FBVCMADescription Out;
    const bool bFound = Reg->FindByName(TEXT("Player"), Out);

    TestTrue(TEXT("FindByName should succeed"), bFound);
    TestEqual(TEXT("Returned name matches"), Out.Name, FString(TEXT("Player")));
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
