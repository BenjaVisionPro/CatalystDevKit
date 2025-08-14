// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCEnvelope.h"

/**
 * FBVCMessageWriter
 * Takes an opaque message (byte blob) and splits it into one-or-more FBVCEnvelope
 * fragments using a fixed maximum payload size per envelope. Emits envelopes via
 * a multicast, or returns them to caller (BuildMessage).
 *
 * No thread-safety guarantees; typically used on a worker thread.
 */
class CATALYSTCONNECT_API FBVCMessageWriter
{
public:
    // Called once per envelope produced
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnvelopeReady, const FBVCEnvelope& /*Env*/);

    FBVCMessageWriter() = default;

    /** Default per-envelope payload cap (bytes). Safe for typical MTUs; override in tests. */
    void  SetMaxFragmentPayload(int32 Bytes) { MaxFragmentPayload = FMath::Max(0, Bytes); }
    int32 GetMaxFragmentPayload() const      { return MaxFragmentPayload; }

    /** Delegate access */
    FOnEnvelopeReady& OnEnvelopeReady() { return EnvelopeReady; }

    // ----------------------------- Build (return envelopes) -----------------------------

    /** Generate a new message id and build envelopes from raw pointer/size. */
    TArray<FBVCEnvelope> BuildMessage(uint16 ChannelId, uint8 Priority, const uint8* Data, int32 Size) const;

    /** Span/view convenience */
    TArray<FBVCEnvelope> BuildMessage(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data) const;

    /** Array convenience */
    TArray<FBVCEnvelope> BuildMessage(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Data) const;

    /** Build using a specific MessageId (uint32). */
    TArray<FBVCEnvelope> BuildMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size) const;

    // ----------------------------- Send (broadcast envelopes) ---------------------------

    /** Generate a new message id and broadcast envelopes (one delegate call per envelope). */
    void SendMessage(uint16 ChannelId, uint8 Priority, const uint8* Data, int32 Size);

    void SendMessage(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data);
    void SendMessage(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Data);

    /** Use an explicit MessageId and broadcast envelopes. */
    void SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size);
    void SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, TArrayView<const uint8> Data);
    void SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const TArray<uint8>& Data);

private:
    /** Core split logic used by both Build and Send paths. */
    void BuildInternal(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size, TArray<FBVCEnvelope>& Out) const;

    /** Monotonic uint32 message id generator (never 0). */
    static uint32 NextMessageId();

private:
    FOnEnvelopeReady EnvelopeReady;
    int32            MaxFragmentPayload = 1200; // conservative default
};
