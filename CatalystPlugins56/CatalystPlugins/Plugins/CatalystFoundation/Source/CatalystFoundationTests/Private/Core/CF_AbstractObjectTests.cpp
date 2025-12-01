#include "Misc/AutomationTest.h"
#include "Model/CFAbstractObject.h"
#include "Model/CFObjectWithTitleAndComment.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_AbstractObject_GuidRoundTrip,
    "CF.AbstractObject.GuidRoundTrip",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_AbstractObject_GuidRoundTrip::RunTest(const FString& Parameters)
{
    const FGuid G = FGuid::NewGuid();
    const FCFAbstractObject Obj(G);
    TestEqual(TEXT("Id should equal ctor arg"), Obj.Id, G);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCF_TitleComment_Defaults,
    "CF.TitleComment.Defaults",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCF_TitleComment_Defaults::RunTest(const FString& Parameters)
{
    const FCFObjectWithTitleAndComment T;
    TestTrue(TEXT("Title should default empty"), T.Title.IsEmpty());
    TestTrue(TEXT("Comment should default empty"), T.Comment.IsEmpty());
    return true;
}