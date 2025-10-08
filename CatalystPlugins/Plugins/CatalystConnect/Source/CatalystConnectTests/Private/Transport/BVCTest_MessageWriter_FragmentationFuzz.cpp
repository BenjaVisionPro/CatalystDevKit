// ============================================
// Copyright © BenjaVision
// ============================================

// Purpose: Prove fragmentation/assembly correctness across random sizes.
// Pipeline under test: MessageWriter -> BVC::Wire::Encode -> EnvelopeReader.HandleInboundFrame
//                      -> MessageReader.OnMessageReady

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCEnvelopeWire.h"

static void MakeDeterministicBytes(TArray<uint8>& Out, int32 Size, uint32 Seed)
{
    Out.SetNumUninitialized(Size);
    // Simple LCG for reproducibility (no <random>).
    uint32 x = Seed ? Seed : 1u;
    for (int32 i = 0; i < Size; ++i)
    {
        x = 1664525u * x + 1013904223u;
        Out[i] = static_cast<uint8>(x >> 24);
    }
}

// Concatenate many byte arrays
static TArray<uint8> Concat(const TArray<TArray<uint8>>& Parts)
{
    TArray<uint8> Out;
    int32 Total = 0;
    for (const auto& P : Parts) Total += P.Num();
    Out.Reserve(Total);
    for (const auto& P : Parts) Out.Append(P);
    return Out;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageWriter_FragmentationFuzz,
    "BVC.Writer.FragmentationFuzz",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageWriter_FragmentationFuzz::RunTest(const FString& /*Params*/)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);
    FBVCEnvelopeReader  EnvReader(Reader);
    FBVCMessageWriter   Writer;

    // Cover a range of sizes and fragment caps, fully in production APIs
    const uint16 Channel  = 9;
    const uint8  Priority = 3;

    // (MsgSize, MaxFrag) pairs
    const struct { int32 Size; int32 MaxFrag; } Cases[] = {
        { 0,    1 }, { 1,    1 }, { 9,    3 }, { 9,    4 }, { 31,   5 },
        { 64,  16 }, { 128, 32 }, { 255, 37 }, { 1024, 120 }, { 4096, 333 },
        { 7777, 777 }, { 16384, 1200 } // typical MTU-ish cap
    };

    for (int i = 0; i < UE_ARRAY_COUNT(Cases); ++i)
    {
        const int32 MsgSize = Cases[i].Size;
        const int32 MaxFrag = Cases[i].MaxFrag;

        Writer.SetMaxFragmentPayload(MaxFrag);

        // Create deterministic payload
        TArray<uint8> Payload;
        MakeDeterministicBytes(Payload, MsgSize, /*Seed*/ 0xDA7A000u + i);

        // Build envelopes and encode to a single stream
        const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(Channel, Priority, Payload);
        TestTrue(FString::Printf(TEXT("[case %d] writer produced >=1 envelope"), i), Envs.Num() >= 1);

        TArray<uint8> Stream;
        for (const FBVCEnvelope& E : Envs) { BVC::Wire::Encode(E, Stream); }

        // Collect the reassembled payload via Reader
        bool bGot = false;
        TArray<uint8> Collected;
        const FDelegateHandle Handle = Reader.OnMessageReady().AddLambda(
            [&](const FBVCMessageReader::FMessageView& V)
            {
                bGot = true;
                Collected.SetNumUninitialized(V.Size);
                if (V.Size > 0) { FMemory::Memcpy(Collected.GetData(), V.Data, V.Size); }
                // Sanity: header echoes
                TestEqual(TEXT("Channel echo"),  V.ChannelId, Channel);
                TestEqual(TEXT("Priority echo"), V.Priority,  Priority);
            });

        // Feed as a single frame (the EnvelopeReader handles concatenation)
        EnvReader.HandleInboundFrame(Stream);

        TestTrue(FString::Printf(TEXT("[case %d] message dispatched"), i), bGot);
        TestEqual   (FString::Printf(TEXT("[case %d] size"), i), Collected.Num(), Payload.Num());
        TestTrue    (FString::Printf(TEXT("[case %d] data match"), i),
                     Collected.Num() == Payload.Num() &&
                     (Collected.Num() == 0 || FMemory::Memcmp(Collected.GetData(), Payload.GetData(), Payload.Num()) == 0));

        Reader.OnMessageReady().Remove(Handle);
    }

    return true;
}