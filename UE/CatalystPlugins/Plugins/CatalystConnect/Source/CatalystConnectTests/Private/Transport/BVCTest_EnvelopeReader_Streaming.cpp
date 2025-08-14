// ============================================
// Copyright © BenjaVision
// Streaming decode exercises the full production path:
// Writer -> Encode -> (split/concat bytes) -> EnvelopeReader.HandleInboundFrame -> MessageReader.OnMessageReady
// ============================================

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCEnvelopeWire.h"

static TArray<uint8> Concat(const TArray<TArray<uint8>>& Parts)
{
    TArray<uint8> Out;
    int32 Total = 0;
    for (const auto& P : Parts) Total += P.Num();
    Out.Reserve(Total);
    for (const auto& P : Parts) Out.Append(P);
    return Out;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_EnvelopeReader_Streaming, "BVC.Wire.StreamingDecode",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_EnvelopeReader_Streaming::RunTest(const FString& /*Params*/)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);
    FBVCEnvelopeReader  EnvReader(Reader);
    FBVCMessageWriter   Writer;

    // Force actual fragmentation using production API
    Writer.SetMaxFragmentPayload(3);

    // Build a message large enough to span multiple envelopes at MaxFragmentPayload=3
    const TArray<uint8> Payload = { 'a','b','c','d','e','f','g','h','i' };
    const auto Envs = Writer.BuildMessage(/*Channel*/7, /*Priority*/0, Payload);

    TestTrue(TEXT("Writer produced >=2 envelopes"), Envs.Num() >= 2);

    // Encode the first envelope as three parts (simulate slicing)
    TArray<uint8> PartA, PartB, PartC;
    {
        TArray<uint8> Full; BVC::Wire::Encode(Envs[0], Full);
        const int32 A = FMath::Max(1, Full.Num() / 3);
        const int32 B = FMath::Max(1, Full.Num() / 3);
        const int32 C = Full.Num() - (A + B);
        PartA.Append(Full.GetData(), A);
        PartB.Append(Full.GetData() + A, B);
        PartC.Append(Full.GetData() + A + B, C);
    }

    // Encode the rest fully
    TArray<TArray<uint8>> Rest;
    for (int32 i = 1; i < Envs.Num(); ++i)
    {
        TArray<uint8> Bytes; BVC::Wire::Encode(Envs[i], Bytes);
        Rest.Add(MoveTemp(Bytes));
    }

    // Subscribe BEFORE feeding frames
    int32 Calls = 0;
    TArray<uint8> Collected;
    const FDelegateHandle ReaderHandle =
        Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView& View)
        {
            ++Calls;
            Collected = TArray<uint8>(View.Data, View.Size);
        });

    // Feed three slices of the first envelope
    EnvReader.HandleInboundFrame(PartA);
    EnvReader.HandleInboundFrame(PartB);
    EnvReader.HandleInboundFrame(PartC);

    // Now feed the rest concatenated
    EnvReader.HandleInboundFrame(Concat(Rest));

    TestEqual(TEXT("OnMessageReady calls"), Calls, 1);
    TestEqual(TEXT("Payload size"), Collected.Num(), Payload.Num());
    TestTrue(TEXT("Payload bytes match"),
        FMemory::Memcmp(Collected.GetData(), Payload.GetData(), Payload.Num()) == 0);

    Reader.OnMessageReady().Remove(ReaderHandle);
    return true;
}
