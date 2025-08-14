// ============================================
// Copyright © BenjaVision
// ============================================
// Control channel end-to-end:
// Reader -> ControlDispatcher -> Outbound wire bytes (HelloAck / SwitchAck)

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCEnvelopeWire.h"
#include "Transport/BVCControlDispatcher.h"
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCCodecRegistry.h"
#include "Transport/BVCProtocolIds.h" // BVC::ECtrlType, BVC::ControlChannelId

// Small helper: decode a concatenated wire stream into envelopes
static TArray<FBVCEnvelope> DecodeAll(const TArray<uint8>& Wire)
{
    TArray<FBVCEnvelope> Out;
    int32 Off = 0;
    FBVCEnvelope Env;
    while (BVC::Wire::Decode(Wire, Off, Env))
    {
        Out.Add(Env);
    }
    return Out;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_Control_HelloAndSwitch,
    "BVC.Control.HelloAndSwitch",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_Control_HelloAndSwitch::RunTest(const FString&)
{
    // Arrange system under test
    FBVCChannelRegistry Channels;
    FBVCCodecRegistry   Codecs;
    FBVCMessageReader   Reader(Channels);
    FBVCMessageWriter   Writer;
    FBVCControlDispatcher Dispatcher(Reader, Writer, Channels, Codecs);

    // Capture outbound wire emitted by ControlDispatcher
    TArray<uint8> CapturedWire;
    auto Handle = Dispatcher.OnOutboundWire.AddLambda([&](const TArray<uint8>& Bytes)
    {
        CapturedWire.Append(Bytes);
    });

    // -------- Hello -> HelloAck --------
    CapturedWire.Reset();

    const uint8 Proposed = Codecs.GetDefaultCodecId(); // propose something we know is accepted
    const TArray<uint8> HelloPayload = FBVCControlDispatcher::MakeHello(Proposed);

    // Build a control message and feed envelopes to Reader (Dispatcher is hooked to Reader)
    {
        const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(BVC::ControlChannelId, /*Priority*/0, HelloPayload);
        for (const FBVCEnvelope& E : Envs) { Reader.PushEnvelope(E); }
    }

    // Assert: outbound contains HelloAck with accepted codec id
    {
        const TArray<FBVCEnvelope> Acks = DecodeAll(CapturedWire);
        TestTrue(TEXT("Hello produced at least one ack envelope"), Acks.Num() >= 1);
        if (Acks.Num() >= 1)
        {
            const TArray<uint8>& P = Acks[0].Payload;
            TestTrue(TEXT("HelloAck payload size >= 2"), P.Num() >= 2);
            if (P.Num() >= 2)
            {
                TestEqual(TEXT("Ack[0] == HelloAck"), (uint8)P[0], (uint8)BVC::ECtrlType::HelloAck);
                // Accepted codec id is P[1]; should be either Proposed or Default depending on registry policy.
                TestEqual(TEXT("Accepted codec id echoes proposal/default"), (uint8)P[1], Proposed);
            }
        }
    }

    // -------- SwitchCodec -> SwitchAck --------
    CapturedWire.Reset();

    const uint16 Chan = 77;
    const uint8  NewCodec = 9; // arbitrary; dispatcher will SetCodec without registry validation

    const TArray<uint8> SwitchPayload = FBVCControlDispatcher::MakeSwitchCodec(Chan, NewCodec);
    {
        const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(BVC::ControlChannelId, /*Priority*/0, SwitchPayload);
        for (const FBVCEnvelope& E : Envs) { Reader.PushEnvelope(E); }
    }

    // Assert: outbound contains SwitchAck with same channel/codec; registry updated
    {
        const TArray<FBVCEnvelope> Acks = DecodeAll(CapturedWire);
        TestTrue(TEXT("Switch produced at least one ack envelope"), Acks.Num() >= 1);
        if (Acks.Num() >= 1)
        {
            const TArray<uint8>& P = Acks[0].Payload;
            TestTrue(TEXT("SwitchAck payload size >= 4"), P.Num() >= 4);
            if (P.Num() >= 4)
            {
                TestEqual(TEXT("Ack[0] == SwitchAck"), (uint8)P[0], (uint8)BVC::ECtrlType::SwitchAck);
                const uint16 AckChan  = (uint16)(P[1] | (P[2] << 8));
                const uint8  AckCodec = P[3];
                TestEqual(TEXT("SwitchAck.Channel"), AckChan, Chan);
                TestEqual(TEXT("SwitchAck.Codec"),   AckCodec, NewCodec);
            }
        }

        // Verify channel registry reflects the change
        FBVCChannelState* State = nullptr;
        const bool bFound = Channels.TryGetState(Chan, State);
        TestTrue(TEXT("Channel state exists after SwitchCodec"), bFound && State != nullptr);
        if (bFound && State)
        {
            TestEqual(TEXT("Channel codec id updated"), State->CodecId, NewCodec);
        }
    }

    Dispatcher.OnOutboundWire.Remove(Handle);
    return true;
}
