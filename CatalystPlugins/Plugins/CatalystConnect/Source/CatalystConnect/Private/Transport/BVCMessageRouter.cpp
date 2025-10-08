// ============================================
// Copyright © BenjaVision
// ============================================
#include "Transport/BVCMessageRouter.h"

void FBVCMessageRouter::Route(const FBVCMessageView& View)
{
    // Broadcast to "any" listeners
    if (AnyChannel.IsBound())
    {
        AnyChannel.Broadcast(View);
    }

    // Broadcast to channel listeners (if any)
    if (FOnChannelMessage* Channel = ChannelMap.Find(View.ChannelId))
    {
        if (Channel->IsBound())
        {
            Channel->Broadcast(View);
        }
    }
}

bool FBVCMessageRouter::HasAnyListeners() const
{
    return AnyChannel.IsBound();
}

bool FBVCMessageRouter::HasChannelListeners(uint16 ChannelId) const
{
    if (const FOnChannelMessage* Channel = ChannelMap.Find(ChannelId))
    {
        return Channel->IsBound();
    }
    return false;
}
