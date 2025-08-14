#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageReader_EdgeCases,
    "BVC.MessageReader.EdgeCases",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageReader_EdgeCases::RunTest(const FString&)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);

    const uint32 MsgId = 222u;

    // fragment arrives out of order -> should be dropped (no crash)
    FBVCEnvelope A; A.ChannelId=1; A.Priority=0; A.Flags=0x01;      A.MessageId=MsgId; A.TotalLength=6; A.SequenceInMessage=0; A.Payload={'a','b','c'};
    FBVCEnvelope B; B.ChannelId=1; B.Priority=0; B.Flags=0x04;      B.MessageId=MsgId; B.TotalLength=6; B.SequenceInMessage=2; B.Payload={'x','y','z'};

    bool bGot=false;
    Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView&)
    {
        bGot = true;
    });

    Reader.PushEnvelope(B);
    Reader.PushEnvelope(A);

    TestFalse(TEXT("No message should be emitted"), bGot);
    return true;
}
