// ============================================
// Copyright © BenjaVision
// ============================================

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_MessageReader_DuplicateFragment,
    "BVC.Reader.DuplicateFragmentIsIgnored",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_MessageReader_DuplicateFragment::RunTest(const FString&)
{
    FBVCChannelRegistry Channels;
    FBVCMessageReader   Reader(Channels);
    FBVCMessageWriter   Writer;
    Writer.SetMaxFragmentPayload(3);

    const uint16 Channel  = 11;
    const uint8  Priority = 0;
    const TArray<uint8> Payload = { 'd','u','p','l','i','c','a','t','e' };

    const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(Channel, Priority, Payload);
    TestTrue(TEXT("Writer produced >=2 envelopes"), Envs.Num() >= 2);
    if (Envs.Num() < 2) return false;

    int32 Calls = 0;
    const uint32 ExpectSize = Payload.Num();
    auto Handle = Reader.OnMessageReady().AddLambda([&](const FBVCMessageReader::FMessageView& V)
    {
        ++Calls;
        TestEqual(TEXT("Size matches payload"), V.Size, (int32)ExpectSize);
        TestEqual(TEXT("Channel matches"), V.ChannelId, Channel);
        TestEqual(TEXT("Priority matches"), V.Priority, Priority);
    });

    // Push first fragment twice (duplicate), then the remaining correct sequence.
    Reader.PushEnvelope(Envs[0]); // first
    Reader.PushEnvelope(Envs[0]); // duplicate of first (should cause the in-flight to reset/drop)
    for (int32 i = 1; i < Envs.Num(); ++i)
    {
        Reader.PushEnvelope(Envs[i]);
    }

    // Because a duplicate sequence index does not match "next expected", the
    // reader drops the in-flight assembly; thus no completed message should arrive.
    TestEqual(TEXT("No message emitted after duplicate fragment"), Calls, 0);

    Reader.OnMessageReady().Remove(Handle);
    return true;
}