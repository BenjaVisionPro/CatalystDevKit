#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Transport/BVCEnvelopeWire.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_EnvelopeWire,
    "BVC.Transport.EnvelopeWire",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FBVCTest_EnvelopeWire::RunTest(const FString&)
{
    FBVCEnvelope E;
    E.ChannelId        = 7;
    E.Priority         = 2;
    E.Flags            = 0x01 | 0x04;
    E.MessageId        = 42u;                        // uint32
    E.TotalLength      = 3;
    E.SequenceInMessage= 0;
    E.Payload          = { 'a', 'b', 'c' };

    TArray<uint8> Wire;
    TestTrue(TEXT("Encode"), FBVCEnvelopeWire::Encode(E, Wire));

    FBVCEnvelope Decoded;
    TestTrue(TEXT("Decode"), FBVCEnvelopeWire::Decode(Wire, Decoded));

    TestEqual(TEXT("ChannelId"),         (int32)Decoded.ChannelId, (int32)E.ChannelId);
    TestEqual(TEXT("Priority"),          (int32)Decoded.Priority,  (int32)E.Priority);
    TestEqual(TEXT("Flags"),             (int32)Decoded.Flags,     (int32)E.Flags);
    TestEqual(TEXT("MessageId"),         Decoded.MessageId,        E.MessageId);
    TestEqual(TEXT("TotalLength"),       (int32)Decoded.TotalLength, (int32)E.TotalLength);
    TestEqual(TEXT("SequenceInMessage"), (int32)Decoded.SequenceInMessage, (int32)E.SequenceInMessage);
    TestEqual(TEXT("Payload.Len"),       Decoded.Payload.Num(),    E.Payload.Num());
    return true;
}
