#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageReader_Basics,
    "BVC.MessageReader.Basics",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageReader_Basics::RunTest(const FString&)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);

    // single-frame envelope
    FBVCEnvelope E;
    E.ChannelId=1; E.Priority=0; E.Flags=0x01|0x04;
    const uint32 MessageId = 1001u;
    E.MessageId = MessageId;
    E.TotalLength=3; E.SequenceInMessage=0; E.Payload={'o','n','e'};

    bool bGot=false, bIdOk=false;
    Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView& View)
    {
        bGot  = true;
        bIdOk = (View.MessageId == MessageId);
    });

    Reader.PushEnvelope(E);
    TestTrue(TEXT("Got message"), bGot);
    TestTrue(TEXT("MessageId correct"), bIdOk);
    return true;
}
