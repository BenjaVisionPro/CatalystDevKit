// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCEnvelope.h"
#include "Transport/BVCChannelRegistry.h"

/**
 * MessageReader takes decoded envelopes and emits whole message byte blobs
 * after reassembly. Transport/codec agnostic; payload is opaque.
 *
 * Data pointer in FMessageView is valid only until delegate returns.
 * For empty messages (Size==0) Data may be nullptr.
 */
class CATALYSTCONNECT_API FBVCMessageReader
{
public:
    struct FMessageView
    {
        uint16       ChannelId = 0;
        uint8        Priority  = 0;
        uint32       MessageId = 0;
        const uint8* Data      = nullptr; // may be nullptr if Size==0
        int32        Size      = 0;
    };

    // Fires on the thread that calls PushEnvelope()
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageReady, const FMessageView&);
    FOnMessageReady& OnMessageReady() { return MessageReady; }

    explicit FBVCMessageReader(FBVCChannelRegistry& InRegistry);

    // Feed a single decoded envelope
    void PushEnvelope(const FBVCEnvelope& Env);

    // Reassembly/limits configuration
    void SetMaxMessageBytes(int32 InBytes)           { MaxMessageBytes = InBytes; }
    void SetFragmentTimeoutSeconds(double InSeconds) { FragmentTimeoutSeconds = InSeconds; }
    void GarbageCollectTimedOut(double NowSeconds);

private:
    FBVCChannelRegistry& Registry;
    FOnMessageReady      MessageReady;

    int32  MaxMessageBytes        = 16 * 1024 * 1024; // 16 MB default
    double FragmentTimeoutSeconds = 10.0;

    // Storage to keep completed blobs alive during delegate dispatch
    TArray<TArray<uint8>> ScratchCompleted;
};
