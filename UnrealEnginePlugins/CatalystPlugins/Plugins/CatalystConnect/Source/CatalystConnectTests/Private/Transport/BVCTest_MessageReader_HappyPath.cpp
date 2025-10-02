// ============================================
// Tests – MessageReader Happy Path
// ============================================
#include "Misc/AutomationTest.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCEnvelope.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageReader_HappyPath,
    "BVC.MessageReader.HappyPath.SingleOrMultiFragment",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageReader_HappyPath::RunTest(const FString& Parameters)
{
    FBVCChannelRegistry Registry;
    FBVCMessageReader   Reader(Registry);

    bool   bCalled    = false;
    bool   bChannelOk = false;
    bool   bPrioOk    = false;
    bool   bMsgIdOk   = false;
    bool   bSizeOk    = false;

    uint16 Channel = 7;
    uint8  Prio    = 3;
    uint32 MsgId   = 123456u;    // unified uint32
    TArray<uint8> Blob = {1,2,3,4,5};

    Reader.OnMessageReady().AddLambda(
        [&](const FBVCMessageReader::FMessageView& View)
        {
            bCalled    = true;
            bChannelOk = (View.ChannelId == Channel);
            bPrioOk    = (View.Priority  == Prio);
            bMsgIdOk   = (View.MessageId == MsgId);
            bSizeOk    = (View.Size == Blob.Num());
        });

    // Single-frame envelope
    FBVCEnvelope Env;
    Env.ChannelId         = Channel;
    Env.Priority          = Prio;
    Env.MessageId         = MsgId;       // uint32
    Env.Flags             = 0x01 | 0x04; // start+end
    Env.SequenceInMessage = 0;
    Env.TotalLength       = Blob.Num();
    Env.Payload           = Blob;

    Reader.PushEnvelope(Env);

    TestTrue(TEXT("Callback fired"), bCalled);
    TestTrue(TEXT("Channel OK"),     bChannelOk);
    TestTrue(TEXT("Priority OK"),    bPrioOk);
    TestTrue(TEXT("MessageId OK"),   bMsgIdOk);
    TestTrue(TEXT("Size OK"),        bSizeOk);

    return true;
}
