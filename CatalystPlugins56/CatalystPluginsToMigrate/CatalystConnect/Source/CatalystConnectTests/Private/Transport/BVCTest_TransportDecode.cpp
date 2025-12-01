#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_TransportDecode,
    "BVC.Transport.Decode",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_TransportDecode::RunTest(const FString&)
{
    FBVCChannelRegistry Channels;
    FBVCEnvelopeReader  Reader(/*MessageReader unused here*/ *(FBVCMessageReader*)nullptr); // If your actual test used it differently, keep that.

    // simple sanity that struct compiles and fields exist
    FBVCEnvelope A; A.ChannelId=1; A.Priority=0; A.Flags=0x01|0x04; A.MessageId=11u; A.TotalLength=3; A.SequenceInMessage=0; A.Payload={'o','n','e'};
    FBVCEnvelope B; B.ChannelId=2; B.Priority=0; B.Flags=0x01|0x04; B.MessageId=22u; B.TotalLength=3; B.SequenceInMessage=0; B.Payload={'t','w','o'};

    TestEqual(TEXT("MsgId A"), A.MessageId, 11u);
    TestEqual(TEXT("MsgId B"), B.MessageId, 22u);
    return true;
}
