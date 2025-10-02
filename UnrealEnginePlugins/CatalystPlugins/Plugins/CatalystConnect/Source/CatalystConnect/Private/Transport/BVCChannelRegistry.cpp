// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCChannelRegistry.h"

FBVCChannelState& FBVCChannelRegistry::GetOrCreate(uint16 ChannelId)
{
    return Map.FindOrAdd(ChannelId);
}

bool FBVCChannelRegistry::TryGetState(uint16 ChannelId, FBVCChannelState*& OutState)
{
    if (FBVCChannelState* Found = Map.Find(ChannelId))
    {
        OutState = Found;
        return true;
    }
    OutState = nullptr;
    return false;
}

void FBVCChannelRegistry::ForEachState(TFunctionRef<void(uint16, FBVCChannelState&)> Fn)
{
    for (auto& Pair : Map)
    {
        Fn(Pair.Key, Pair.Value);
    }
}

void FBVCChannelRegistry::SetCodec(uint16 ChannelId, uint8 CodecId)
{
    FBVCChannelState& State = GetOrCreate(ChannelId);
    State.CodecId = CodecId;
}
