// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCEnvelopeWire.h"

FBVCEnvelopeReader::FBVCEnvelopeReader(FBVCMessageReader& InMessageReader)
    : MessageReader(InMessageReader)
{
}

void FBVCEnvelopeReader::HandleInboundFrame(const TArray<uint8>& Bytes)
{
    // In-place append to avoid building a temporary "Combined" buffer.
    if (Bytes.Num() > 0)
    {
        const int32 OldNum = Pending.Num();
        Pending.AddUninitialized(Bytes.Num());
        FMemory::Memcpy(Pending.GetData() + OldNum, Bytes.GetData(), Bytes.Num());
    }

    int32        Offset = 0;
    FBVCEnvelope Env;

    // Decode as many envelopes as are fully present in Pending.
    while (true)
    {
        const int32 PrevOffset = Offset;

        if (!BVC::Wire::Decode(Pending, Offset, Env))
        {
            break; // not enough bytes for another envelope yet
        }

        // Defensive: ensure decoder advanced the cursor to prevent infinite loops.
        checkf(Offset > PrevOffset,
               TEXT("BVC::Wire::Decode did not advance the offset (Prev=%d, Cur=%d)."),
               PrevOffset, Offset);

        // Hand off decoded envelope to the message reader (reassembly / dispatch).
        MessageReader.PushEnvelope(Env);
    }

    // Discard consumed prefix; keep any remainder without shrinking capacity.
    if (Offset > 0)
    {
        Pending.RemoveAt(0, Offset, EAllowShrinking::No);
    }
}
