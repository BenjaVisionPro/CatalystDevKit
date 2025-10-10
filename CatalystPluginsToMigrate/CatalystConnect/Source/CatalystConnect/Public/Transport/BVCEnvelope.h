// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/**
 * Lowest-level decoded “envelope” produced by the envelope reader.
 * This is transport/codec-agnostic and contains one message fragment
 * or a complete (single-frame) message.
 */
struct CATALYSTCONNECT_API FBVCEnvelope
{
    // Routing / priority
    uint16 ChannelId         = 0;
    uint8  Priority          = 0;

    // Unified message identifier across the pipeline
    uint32 MessageId         = 0;

    // Fragmentation metadata
    // bit0 = Start, bit2 = End (same as before)
    uint8  Flags             = 0;
    uint16 SequenceInMessage = 0;
    uint32 TotalLength       = 0;   // total un-fragmented message length (bytes)

    // Opaque payload for this fragment (or whole message if single-frame)
    TArray<uint8> Payload;
};
