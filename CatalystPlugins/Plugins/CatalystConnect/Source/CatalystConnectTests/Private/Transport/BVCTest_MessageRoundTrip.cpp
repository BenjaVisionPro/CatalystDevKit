// ============================================
// Copyright © BenjaVision
// ============================================

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCEnvelopeWire.h"   // BVC::Wire
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageRoundTrip,
    "BVC.RoundTrip.Message",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageRoundTrip::RunTest(const FString&)
{
    FBVCMessageWriter   Writer;
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);

    // Capture envelopes from the writer
    TArray<FBVCEnvelope> Produced;
    const FDelegateHandle ProducedHandle =
        Writer.OnEnvelopeReady().AddLambda([&](const FBVCEnvelope& Env){ Produced.Add(Env); });

    // Subscribe to the reader BEFORE feeding any data
    bool bGot = false;
    FBVCMessageReader::FMessageView Last{};
    const FDelegateHandle ReaderHandle =
        Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView& V)
        {
            bGot = true;
            Last = V; // safe: View points to Reader's stable scratch during broadcast
        });

    // Prepare a message
    const uint16 Channel  = 7;
    const uint8  Priority = 1;
    const uint32 MsgId    = 0x13572468u;
    const TArray<uint8> Payload = { 'r','o','u','n','d','t','r','i','p' };

    // Build envelopes (broadcast path)
    Writer.SendMessage(Channel, Priority, MsgId, Payload);

    // Simulate a wire stream by appending encodes
    TArray<uint8> WireBytes;
    for (const FBVCEnvelope& Env : Produced)
    {
        BVC::Wire::Encode(Env, WireBytes); // appends by design
    }

    // Decode and feed to reader
    int32 Off = 0; FBVCEnvelope Env;
    while (BVC::Wire::Decode(WireBytes, Off, Env))
    {
        Reader.PushEnvelope(Env);
    }

    // Assertions
    TestTrue(TEXT("Message dispatched"), bGot);
    TestEqual(TEXT("Channel"),  Last.ChannelId, Channel);
    TestEqual(TEXT("Priority"), Last.Priority,  Priority);
    TestEqual(TEXT("MessageId"),Last.MessageId, MsgId);
    TestEqual(TEXT("Size"),     Last.Size,      Payload.Num());

    // Cleanup delegates
    Writer.OnEnvelopeReady().Remove(ProducedHandle);
    Reader.OnMessageReady().Remove(ReaderHandle);

    return true;
}
