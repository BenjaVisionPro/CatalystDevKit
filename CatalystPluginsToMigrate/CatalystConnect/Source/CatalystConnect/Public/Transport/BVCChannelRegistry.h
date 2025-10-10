// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

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
