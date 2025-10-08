// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/**
 * IBVCFlowControl
 * - Optional facade used by UBVCConnectionManager and the transport worker.
 * - Supports rate caps (bytes/sec) and backpressure signals (on/off).
 * - Implementations may block/sleep in BeforeSend() to enforce pacing.
 */
class IBVCFlowControl : public TSharedFromThis<IBVCFlowControl>
{
public:
    virtual ~IBVCFlowControl() = default;

    // ----- Rate configuration (0 == unlimited) -----
    virtual void  SetMaxOutboundBytesPerSecond(int64 BytesPerSecond) = 0;
    virtual int64 GetMaxOutboundBytesPerSecond() const = 0;

    virtual void  SetMaxInboundBytesPerSecond(int64 BytesPerSecond) = 0;
    virtual int64 GetMaxInboundBytesPerSecond() const = 0;

    // ----- Backpressure hooks (from worker) -----
    virtual void SetInboundBackpressure(bool bActive)  = 0;
    virtual void SetOutboundBackpressure(bool bActive) = 0;

    // ----- Pacing hook (called by ConnectionManager before Transport->SendBytes) -----
    // Implementations may Sleep to maintain the configured rate cap.
    virtual void BeforeSend(int32 PayloadBytes) = 0;
};