// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCEnvelope.h"

/**
 * FBVCEnvelopeWire
 *
 * Single-envelope coder/decoder. Assumes buffer starts at an envelope boundary.
 * For concatenated byte streams use BVC::Wire::Decode(Bytes, Offset, Out).
 */
struct CATALYSTCONNECT_API FBVCEnvelopeWire
{
    // Append one encoded envelope to OutBytes (does NOT reset OutBytes).
    static bool Encode(const FBVCEnvelope& Env, TArray<uint8>& OutBytes);

    // Decode one envelope from the start of InBytes into OutEnv.
    // Returns true if a full header+payload fit in InBytes.
    static bool Decode(const TArray<uint8>& InBytes, FBVCEnvelope& OutEnv);

    // Convenience constructor for tests/tools.
    static FBVCEnvelope MakeQuick(uint16 Channel,
                                  uint8  Priority,
                                  uint8  Flags,
                                  uint32 MsgId,
                                  uint32 Total,
                                  uint16 Seq,
                                  TArray<uint8> Payload);
};

/**
 * Streaming helpers used by production paths and tests.
 * They operate on a concatenated byte buffer and maintain a moving Offset.
 */
namespace BVC { namespace Wire
{
    // Fixed header size: chan(2) + pri(1) + flags(1) + msgId(4) + total(4) + seq(2) + payloadLen(4)
    inline constexpr int32 kHeaderBytes = 2 + 1 + 1 + 4 + 4 + 2 + 4;

    // Append one envelope’s bytes to Out.
    CATALYSTCONNECT_API void Encode(const FBVCEnvelope& Env, TArray<uint8>& Out);

    // Streaming decode from Bytes starting at Offset; advances Offset on success.
    // Returns true if a full envelope (header+payload) was decoded.
    CATALYSTCONNECT_API bool Decode(const TArray<uint8>& Bytes, int32& Offset, FBVCEnvelope& Out);
}} // namespace BVC::Wire
