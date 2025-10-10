// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Templates/UniquePtr.h"
#include "Containers/Queue.h"
#include "Transport/BVCEnvelope.h"

// -------------------------------- Flow Control -------------------------------
#include "Transport/FlowControl/IBVCFlowControl.h"

// Lightweight bounded MPSC wrapper over TQueue with counters.
template<typename T>
class FBVCBoundedMpscQueue
{
public:
    FBVCBoundedMpscQueue() = default;
    explicit FBVCBoundedMpscQueue(int32 InCapacity) : Capacity(FMath::Max(1, InCapacity)) {}

    // Movable (we move counters and swap queues); not copyable.
    FBVCBoundedMpscQueue(FBVCBoundedMpscQueue&& Other) noexcept { *this = MoveTemp(Other); }
    FBVCBoundedMpscQueue& operator=(FBVCBoundedMpscQueue&& Other) noexcept
    {
        if (this != &Other)
        {
            Capacity = Other.Capacity;
            Depth.Store(Other.Depth.Load());
            Drops.Store(Other.Drops.Load());
            Swap(Q, Other.Q); // swap queue pointers
        }
        return *this;
    }

    bool Enqueue(const T& Item)
    {
        if (Depth.Load() >= Capacity) { Drops.IncrementExchange(); return false; }
        Q->Enqueue(Item);
        Depth.IncrementExchange();
        return true;
    }
    bool Enqueue(T&& Item)
    {
        if (Depth.Load() >= Capacity) { Drops.IncrementExchange(); return false; }
        Q->Enqueue(MoveTemp(Item));
        Depth.IncrementExchange();
        return true;
    }

    bool TryEnqueue(const T& Item) { return Enqueue(Item); }
    bool TryEnqueue(T&& Item)      { return Enqueue(MoveTemp(Item)); }

    bool Dequeue(T& Out)
    {
        if (!Q->Dequeue(Out)) { return false; }

        // Depth-- with clamp at 0 using CAS (avoids underflow).
        for (;;)
        {
            int32 Cur = Depth.Load();
            if (Cur <= 0) { break; }
            int32 Expected = Cur;
            if (Depth.CompareExchange(Expected, Cur - 1)) { break; }
        }
        return true;
    }

    int32 GetCapacity() const { return Capacity; }
    void  SetCapacity(int32 InCap) { Capacity = FMath::Max(1, InCap); }

    int32 GetDepth() const { return Depth.Load(); }
    int32 GetDrops() const { return Drops.Load(); }
    void  ResetDrops()     { Drops.Store(0); }

    // Peeking “is there work” without popping
    bool Peek(T& /*DummyOut*/) const { return !Q->IsEmpty(); }

private:
    // Store queue in a UniquePtr so we can “move” by swapping pointers.
    TUniquePtr<TQueue<T, EQueueMode::Mpsc>> Q = MakeUnique<TQueue<T, EQueueMode::Mpsc>>();
    int32   Capacity = 1024;
    TAtomic<int32> Depth {0};
    TAtomic<int32> Drops {0};
};

// -------------------------------- Metrics / Config ---------------------------

struct FBVCWorkerMetrics
{
    int32 InboundDepth  = 0;
    int32 InboundPeak   = 0; // (reserved for future use)
    int32 InboundDrops  = 0;

    int32 OutboundDepth = 0;
    int32 OutboundPeak  = 0; // (reserved for future use)
    int32 OutboundDrops = 0;

    // Snapshot of configured flow limits (0 == unlimited).
    int64 MaxOutboundBytesPerSecond = 0;
    int64 MaxInboundBytesPerSecond  = 0;
};

struct FBVCTransportConfig
{
    // Log warnings when depth >= WarnPercent of capacity (0 disables).
    int32 WarnPercent      = 90;
    // Emit a drop log every N drops (clamped to >=1).
    int32 LogEveryNDrops   = 100;

    // Backpressure hysteresis thresholds (percent of capacity).
    int32 HighWaterPercent = 85;
    int32 LowWaterPercent  = 60;

    // Queue capacities (can be updated at runtime).
    int32 InboundHardMaxItems  = 1024;
    int32 OutboundHardMaxItems = 1024;

    // Flow control limits (0 == unlimited). Dynamically configurable.
    int64 MaxOutboundBytesPerSecond = 0; // throttle send path
    int64 MaxInboundBytesPerSecond  = 0; // reserved (not enforced in worker yet)
};

class UBVCConnectionManager;
class FBVCEnvelopeReader;
class FBVCMessageReader;
class FBVCMessageWriter;

/** Worker broadcasts simple connected/disconnected events as a bool. */
DECLARE_MULTICAST_DELEGATE_OneParam(FBVCOnConnectionStateWorker, bool /*bConnected*/);

/** Backpressure change signals per-queue. */
DECLARE_MULTICAST_DELEGATE_OneParam(FBVCOnBackpressureChanged, bool /*bActive*/);

/**
 * FBVCTransportWorker
 */
class CATALYSTCONNECT_API FBVCTransportWorker : public FRunnable
{
public:
    FBVCTransportWorker(UBVCConnectionManager& InConnection,
                        FBVCEnvelopeReader&    InEnvelopeReader,
                        FBVCMessageReader&     InMessageReader);
    virtual ~FBVCTransportWorker();

    /** Replace config at runtime (hot-reload). */
    void Configure(const FBVCTransportConfig& InConfig);

    /** Optionally inject a custom flow controller (else a default token bucket is used). */
    void SetFlowController(const TSharedPtr<IBVCFlowControl>& InFlow);

    /** Enqueue a message to send (channel/priority/payload). Thread-safe. */
    void Send(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data);

    /** FRunnable */
    virtual bool   Init() override;
    virtual uint32 Run()  override;
    void Stop();

    /** Connected state (bool) broadcast; currently emitted on Connect/Disconnect paths. */
    FBVCOnConnectionStateWorker& OnConnectionStateWorker() { return ConnectionStateWorker; }

    /** Backpressure delegates */
    FBVCOnBackpressureChanged& OnInboundBackpressure()  { return InboundBackpressureChanged; }
    FBVCOnBackpressureChanged& OnOutboundBackpressure() { return OutboundBackpressureChanged; }

    /** Introspection */
    void GetMetrics(FBVCWorkerMetrics& Out) const;

private:
    /** Called on transport/IO thread by ConnectionManager; enqueues bytes then wakes the worker. */
    void OnInboundFromTransport(const TArray<uint8>& WireBytes);

    /** Drain inbound queue -> EnvelopeReader */
    void DrainInbound();

    /** Drain outbound queue -> ConnectionManager */
    void DrainOutbound();

    /** Depth warnings & drop logs */
    void MaybeWarnInboundDepth()  const;
    void MaybeWarnOutboundDepth() const;
    void MaybeLogInboundDrop()    const;
    void MaybeLogOutboundDrop()   const;

    /** Backpressure (hysteresis) maintenance */
    void MaybeUpdateInboundBackpressure()  const;
    void MaybeUpdateOutboundBackpressure() const;
    bool IsInboundBackpressureActive()  const;
    bool IsOutboundBackpressureActive() const;

    /** Apply flow-control related knobs to the controller (called from Configure). */
    void ApplyFlowConfig();

private:
    // Dependencies (not owned)
    UBVCConnectionManager& Connection;
    FBVCEnvelopeReader&    EnvelopeReader;
    FBVCMessageReader&     MessageReader;

    // Outbound item
    struct FOutbound
    {
        uint16        ChannelId = 0;
        uint8         Priority  = 0;
        TArray<uint8> Payload;
    };

    // Queues (MPSC -> Single consumer)
    FBVCBoundedMpscQueue<TArray<uint8>> InboundQueue;
    FBVCBoundedMpscQueue<FOutbound>     OutboundQueue;

    // Wake/sleep primitive
    FEvent* WakeEvent = nullptr;

    // Thread
    FRunnableThread* Thread = nullptr;
    FThreadSafeBool  bStopRequested = false;

    // Delegate wiring
    FDelegateHandle InboundHandle;

    // Connected-state relay
    FBVCOnConnectionStateWorker ConnectionStateWorker;

    // Backpressure signals (mutable to allow updates in const helpers)
    mutable bool bInboundBackpressured  = false;
    mutable bool bOutboundBackpressured = false;
    FBVCOnBackpressureChanged InboundBackpressureChanged;
    FBVCOnBackpressureChanged OutboundBackpressureChanged;

    // Flow controller
    TSharedPtr<IBVCFlowControl> Flow;

    // Config & counters
    FBVCTransportConfig Config;
    mutable int32 InboundDropsLogged  = 0;
    mutable int32 OutboundDropsLogged = 0;
};
