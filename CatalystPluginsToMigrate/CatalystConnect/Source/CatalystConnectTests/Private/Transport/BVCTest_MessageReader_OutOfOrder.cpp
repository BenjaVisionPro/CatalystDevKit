// ============================================
// Copyright © BenjaVision
// ============================================

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageReader_OutOfOrder,
    "BVC.Reader.OutOfOrderFragmentsAreRejected",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageReader_OutOfOrder::RunTest(const FString&)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);
    FBVCMessageWriter   Writer;
    Writer.SetMaxFragmentPayload(3); // force multiple fragments

    const uint16 Channel  = 10;
    const uint8  Priority = 0;
    const TArray<uint8> Payload = { 'o','o','o','t','e','s','t','!','!' };

    const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(Channel, Priority, Payload);
    TestTrue(TEXT("Writer produced >=2 envelopes"), Envs.Num() >= 2);
    if (Envs.Num() < 2) return false;

    int32 Calls = 0;
    auto Handle = Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView&){ ++Calls; });

    // Push second fragment first (out of order), then first and the rest
    Reader.PushEnvelope(Envs[1]); // out-of-order => should drop in-flight
    for (int32 i = 0; i < Envs.Num(); ++i)
    {
        Reader.PushEnvelope(Envs[i]);
    }

    // Because of the out-of-order push, the in-flight buffer should have been dropped,
    // so we should NOT get a completed message.
    TestEqual(TEXT("Exactly one message after out-of-order then proper restart"), Calls, 1);
    
    Reader.OnMessageReady().Remove(Handle);
    return true;
}
