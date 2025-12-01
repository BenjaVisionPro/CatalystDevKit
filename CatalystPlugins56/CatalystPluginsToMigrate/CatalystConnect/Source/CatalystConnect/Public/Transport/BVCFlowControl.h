// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/**
 * Flow-control interface:
 * - Receives backpressure transitions (ON/OFF) from the worker.
 * - Can pace outbound sends to honor a configured max bytes/second.
 * - Defaults to "unlimited" (no throttling) until configured.
 */
class CATALYSTCONNECT_API IBVCFlowControl
{
public:
    virtual ~IBVCFlowControl() = default;

    /** True if a backpressure condition is currently active (inbound or outbound). */
    virtual void SetInboundBackpressure(bool bActive)  = 0;
    virtual void SetOutboundBackpressure(bool bActive) = 0;

    /** Configure outbound max flow rate. 0 or negative means "unlimited". */
    virtual void SetMaxOutboundBytesPerSecond(double BytesPerSec) = 0;

    /** Configure inbound max flow rate (reserved; not enforced here yet). */
    virtual void SetMaxInboundBytesPerSecond(double BytesPerSec) = 0;

    /** Hook the sender calls right before emitting bytes to the transport. */
    virtual void BeforeSend(int32 NumBytes) = 0;
};

/**
 * Default implementation with simple token-bucket for outbound pacing.
 * Thread-safe. All settings are runtime-configurable.
 *
 * Notes:
 * - Outbound: When MaxOutboundBps > 0, BeforeSend() blocks just enough
 *   to keep the send rate under the configured limit (burst-friendly).
 * - Inbound: MaxInboundBps is stored for future use (not enforced here).
 */
class CATALYSTCONNECT_API FBVCFlowControl_Default : public IBVCFlowControl
{
public:
    FBVCFlowControl_Default();

    // IBVCFlowControl
    virtual void SetInboundBackpressure(bool bActive) override;
    virtual void SetOutboundBackpressure(bool bActive) override;
    virtual void SetMaxOutboundBytesPerSecond(double BytesPerSec) override;
    virtual void SetMaxInboundBytesPerSecond(double BytesPerSec) override;
    virtual void BeforeSend(int32 NumBytes) override;

private:
    void RefillTokens(double NowSeconds);

private:
    mutable FCriticalSection Mutex;

    // Backpressure flags (for future heuristics; no gating today)
    bool bInboundBackpressured  = false;
    bool bOutboundBackpressured = false;

    // Config
    double MaxOutboundBps = 0.0; // <= 0 => unlimited
    double MaxInboundBps  = 0.0; // reserved

    // Token bucket state (for outbound)
    double Tokens       = 0.0; // current tokens (bytes)
    double LastRefillTs = 0.0; // seconds since startup
    double BurstCap     = 0.0; // bytes; if 0, auto = 2 * MaxOutboundBps
};