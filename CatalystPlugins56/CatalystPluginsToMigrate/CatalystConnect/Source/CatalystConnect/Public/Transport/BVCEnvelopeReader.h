// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCEnvelope.h"

class FBVCMessageReader;

/**
 * FBVCEnvelopeReader
 * Accepts raw wire frames (byte blobs), parses zero or more FBVCEnvelope(s),
 * and forwards each decoded envelope to FBVCMessageReader::PushEnvelope.
 *
 * Thread-affinity: call from whatever thread receives transport frames.
 * This class does no locking; caller is responsible for thread-safety.
 */
class CATALYSTCONNECT_API FBVCEnvelopeReader
{
public:
    explicit FBVCEnvelopeReader(FBVCMessageReader& InMessageReader);

    /** Public feed: pass a raw inbound frame (may contain 0..N concatenated envelopes). */
    void HandleInboundFrame(const TArray<uint8>& Bytes);

private:
    FBVCMessageReader& MessageReader;

    // Remainder from previous partial frame
    TArray<uint8> Pending;
};
