// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCEnvelope.h"

// Stateless helpers used by MessageWriter or callers that want direct control.
// These functions only fill envelope fields; they DO NOT encode to wire bytes.
struct CATALYSTCONNECT_API FBVCEnvelopeWriter
{
    // Single-frame (Start|End, Seq=0)
    static void WriteSingle(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Payload, uint32 MessageId, TArray<FBVCEnvelope>& OutEnvelopes);

    // Multi-frame (Start on first, End on last, Seq increments, TotalLength repeated)
    static void WriteFragmented(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Payload, int32 MaxPayloadPerEnvelope, uint32 MessageId, TArray<FBVCEnvelope>& OutEnvelopes);
};
