// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/FlowControl/IBVCFlowControl.h"

/**
 * FBVCTokenBucketFlow
 * - Simple token-bucket limiter with wall-clock pacing.
 * - Thread-safety: designed to be called from a single sending thread
 *   (the BVC transport worker / connection manager), so no heavy locking is used.
 * - Uses FPlatformTime::Seconds() for timing and FPlatformProcess::Sleep()
 *   for short waits when needed.
 */
class FBVCTokenBucketFlow final : public IBVCFlowControl
{
public:
    FBVCTokenBucketFlow()
    {
        Reset();
    }

    // ---- IBVCFlowControl ----
    virtual void SetMaxOutboundBytesPerSecond(int64 BytesPerSecond) override
    {
        MaxOutboundBps = FMath::Max<int64>(BytesPerSecond, 0);
        // Bucket size: allow short bursts up to ~1 second of budget (clamped)
        BucketCapacity = (MaxOutboundBps > 0) ? (double)MaxOutboundBps : BIG_NUMBER;
        Tokens = FMath::Min<double>(Tokens, BucketCapacity);
        LastRefillSeconds = FPlatformTime::Seconds();
    }

    virtual int64 GetMaxOutboundBytesPerSecond() const override
    {
        return MaxOutboundBps;
    }

    virtual void SetMaxInboundBytesPerSecond(int64 BytesPerSecond) override
    {
        MaxInboundBps = FMath::Max<int64>(BytesPerSecond, 0);
    }

    virtual int64 GetMaxInboundBytesPerSecond() const override
    {
        return MaxInboundBps;
    }

    virtual void SetInboundBackpressure(bool bActive) override
    {
        bInboundBackpressured = bActive;
    }

    virtual void SetOutboundBackpressure(bool bActive) override
    {
        bOutboundBackpressured = bActive;
    }

    virtual void BeforeSend(int32 PayloadBytes) override
    {
        if (PayloadBytes <= 0) { return; }
        if (MaxOutboundBps <= 0)
        {
            // Unlimited
            return;
        }

        // Refill tokens
        const double Now = FPlatformTime::Seconds();
        Refill(Now);

        // Consume or wait until enough tokens are available
        const double Need = (double)PayloadBytes;
        while (Tokens < Need)
        {
            const double Missing = Need - Tokens;
            const double SecondsToWait = Missing / (double)MaxOutboundBps;

            // Sleep with a floor to avoid busy waiting; clamp to avoid long pauses
            const double Clamped = FMath::Clamp(SecondsToWait, 0.0005, 0.1000);
            FPlatformProcess::Sleep((float)Clamped);

            const double After = FPlatformTime::Seconds();
            Refill(After);
        }

        Tokens -= Need;

        // Optional: while backpressured, add a tiny nudge to ease pressure
        if (bOutboundBackpressured)
        {
            FPlatformProcess::Sleep(0.001f);
        }
    }

    // Convenience for tests or tools
    void Reset()
    {
        MaxOutboundBps = 0;
        MaxInboundBps  = 0;
        bInboundBackpressured  = false;
        bOutboundBackpressured = false;
        Tokens = BIG_NUMBER;
        BucketCapacity = BIG_NUMBER;
        LastRefillSeconds = FPlatformTime::Seconds();
    }

private:
    void Refill(double Now)
    {
        const double Elapsed = Now - LastRefillSeconds;
        LastRefillSeconds = Now;

        if (MaxOutboundBps > 0)
        {
            Tokens = FMath::Min(Tokens + Elapsed * (double)MaxOutboundBps, BucketCapacity);
        }
        else
        {
            Tokens = BIG_NUMBER;
        }
    }

private:
    int64  MaxOutboundBps = 0;
    int64  MaxInboundBps  = 0;

    bool   bInboundBackpressured  = false;
    bool   bOutboundBackpressured = false;

    double Tokens = 0.0;
    double BucketCapacity = 0.0;
    double LastRefillSeconds = 0.0;
};