#pragma once
#include "CoreMinimal.h"

/**
 * Per-channel runtime state: chosen codec/compression and in-flight partials.
 * No UObject lifetime concerns here; owned by higher-level managers.
 */
struct CATALYSTCONNECT_API FBVCChannelState
{
    // The selected codec for this channel (negotiated elsewhere)
    uint8 CodecId = 0;

    // Optional compression preference (transport still respects per-message flags)
    uint8 PreferredCompression = 0; // 0 = none, 1 = gzip (future)

    // Buffer for assembling multi-fragment messages keyed by MessageId
    struct FPartial
    {
        uint32 Total = 0;
        TArray<uint8> Buffer;
        uint32 NextSequence = 0;
        double LastTouchSeconds = 0.0;
    };

    TMap<FGuid, FPartial> InFlight;
};
