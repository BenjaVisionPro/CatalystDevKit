// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/** Per-channel state (codec + partial reassembly). */
struct CATALYSTCONNECT_API FBVCChannelState
{
    uint8 CodecId = 0;

    struct FPartial
    {
        TArray<uint8> Buffer;
        int32  Total            = 0;
        uint16 NextSequence     = 0;
        double LastTouchSeconds = 0.0;
    };

    // Keyed by uint32 MessageId
    TMap<uint32, FPartial> InFlight;
};

class CATALYSTCONNECT_API FBVCChannelRegistry
{
public:
    FBVCChannelState& GetOrCreate(uint16 ChannelId);
    bool TryGetState(uint16 ChannelId, FBVCChannelState*& OutState);
    void ForEachState(TFunctionRef<void(uint16, FBVCChannelState&)> Fn);
    void SetCodec(uint16 ChannelId, uint8 CodecId);

private:
    TMap<uint16, FBVCChannelState> Map;
};
