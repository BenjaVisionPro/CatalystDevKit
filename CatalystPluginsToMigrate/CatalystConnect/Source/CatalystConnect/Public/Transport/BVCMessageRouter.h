// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

// A lightweight, non-owning view of a decoded message.
// NOTE: Data pointer is valid only for the duration of the dispatch.
struct CATALYSTCONNECT_API FBVCMessageView
{
    uint16        ChannelId = 0;
    uint8         Priority  = 0;
    uint32        MessageId = 0;
    const uint8*  Data      = nullptr;
    int32         Size      = 0;
};

class CATALYSTCONNECT_API FBVCMessageRouter
{
public:
    // Delegates
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyMessage,     const FBVCMessageView&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnChannelMessage, const FBVCMessageView&);

    // Subscribe
    FOnAnyMessage&     OnAny()                           { return AnyChannel; }
    FOnChannelMessage& OnChannel(uint16 ChannelId)       { return ChannelMap.FindOrAdd(ChannelId); }

    // Route a message view to listeners
    void Route(const FBVCMessageView& View);

    // Optional helpers
    bool HasAnyListeners() const;
    bool HasChannelListeners(uint16 ChannelId) const;

private:
    FOnAnyMessage                          AnyChannel;
    TMap<uint16, FOnChannelMessage>        ChannelMap;
};
