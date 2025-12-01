// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/** Raw inbound transport frame (already depacketized by the socket/WS layer). */
DECLARE_MULTICAST_DELEGATE_OneParam(FBVCOnInboundFrame, const TArray<uint8>& /*WireBytes*/);

/**
 * Minimal transport interface used by the ConnectionManager/Worker.
 * Implementations: WebSocket, TCP, HTTP long-polling, etc.
 */
class CATALYSTCONNECT_API IBVCTransportInterface
{
public:
    virtual ~IBVCTransportInterface() = default;

    /** Connect to a fully-qualified URL. Implementation chooses its own threading model. */
    virtual void Connect(const FString& Url) = 0;

    /** Graceful disconnect/close. */
    virtual void Disconnect() = 0;

    /** Transport is considered connected/ready to send? */
    virtual bool IsConnected() const = 0;

    /** Outbound bytes to the wire. Non-blocking strongly preferred. */
    virtual void SendBytes(const TArray<uint8>& Bytes) = 0;

    /** Optional nudge (wake select/poll loop, flush, etc.). No-op by default. */
    virtual void Wake() {}

    /** Subscribe to raw inbound frames (transport thread or impl thread). */
    virtual FBVCOnInboundFrame& OnInboundFrame() = 0;

    /** Human-readable transport name for logging. */
    virtual FString GetDebugName() const = 0;
};
