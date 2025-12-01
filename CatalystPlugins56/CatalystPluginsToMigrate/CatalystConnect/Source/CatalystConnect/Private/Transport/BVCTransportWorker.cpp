// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCTransportWorker.h"

#include "Connection/UBVCConnectionManager.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCEnvelope.h"
#include "Transport/BVCMessageWriter.h"
#include "Transport/BVCEnvelopeWire.h"

#include "HAL/PlatformProcess.h"
#include "Logging/LogMacros.h"

// Flow control (default implementation)
#include "Transport/FlowControl/BVCTokenBucketFlow.h"

DEFINE_LOG_CATEGORY_STATIC(LogBVCWorker, Log, All);

namespace
{
    // Try popping up to N items per loop to stay responsive under burst
    constexpr int32 kMaxBatch = 256;

    FORCEINLINE int32 PercentOf(int32 Percent, int32 Cap)
    {
        Percent = FMath::Clamp(Percent, 0, 100);
        return (Percent * Cap) / 100;
    }
}

FBVCTransportWorker::FBVCTransportWorker(UBVCConnectionManager& InConnection,
                                         FBVCEnvelopeReader&    InEnvelopeReader,
                                         FBVCMessageReader&     InMessageReader)
    : Connection(InConnection)
    , EnvelopeReader(InEnvelopeReader)
    , MessageReader(InMessageReader)
    , InboundQueue(/*MaxItems*/ 1024)
    , OutboundQueue(/*MaxItems*/1024)
{
    // Defaults; caller may Configure() later
    Config = FBVCTransportConfig{};

    // Default flow controller if caller doesn't inject one
    Flow = MakeShared<FBVCTokenBucketFlow>();
    ApplyFlowConfig();

    WakeEvent = FPlatformProcess::GetSynchEventFromPool(/*bIsManualReset*/ false);

    // Route inbound frames from the transport into our inbound queue
    InboundHandle = Connection.OnInboundFrame().AddRaw(this, &FBVCTransportWorker::OnInboundFromTransport);

    // Spin up the worker thread
    Thread = FRunnableThread::Create(this, TEXT("BVC.TransportWorker"), 0, TPri_BelowNormal);
}

FBVCTransportWorker::~FBVCTransportWorker()
{
    // Unhook delegate early to avoid receiving frames during shutdown
    if (InboundHandle.IsValid())
    {
        Connection.OnInboundFrame().Remove(InboundHandle);
        InboundHandle.Reset();
    }

    // Stop thread
    bStopRequested = true;
    if (WakeEvent) { WakeEvent->Trigger(); }

    if (Thread)
    {
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }

    if (WakeEvent)
    {
        FPlatformProcess::ReturnSynchEventToPool(WakeEvent);
        WakeEvent = nullptr;
    }
}

void FBVCTransportWorker::SetFlowController(const TSharedPtr<IBVCFlowControl>& InFlow)
{
    Flow = InFlow ? InFlow : MakeShared<FBVCTokenBucketFlow>();
    ApplyFlowConfig();

    // Re-assert current backpressure states on the new controller
    if (Flow.IsValid())
    {
        Flow->SetInboundBackpressure(bInboundBackpressured);
        Flow->SetOutboundBackpressure(bOutboundBackpressured);
    }
}

void FBVCTransportWorker::Configure(const FBVCTransportConfig& InConfig)
{
    // Swap config
    Config = InConfig;

    // Queue capacities can be adjusted on the fly
    if (InboundQueue.GetCapacity() != Config.InboundHardMaxItems)
    {
        InboundQueue.SetCapacity(Config.InboundHardMaxItems);
    }
    if (OutboundQueue.GetCapacity() != Config.OutboundHardMaxItems)
    {
        OutboundQueue.SetCapacity(Config.OutboundHardMaxItems);
    }

    // Flow control knobs
    ApplyFlowConfig();

    // Immediately recompute backpressure against new thresholds/capacities
    MaybeUpdateInboundBackpressure();
    MaybeUpdateOutboundBackpressure();

    UE_LOG(LogBVCWorker, Verbose, TEXT("Configured: InCap=%d OutCap=%d High=%d%% Low=%d%% OutBps=%lld InBps=%lld"),
        InboundQueue.GetCapacity(), OutboundQueue.GetCapacity(),
        Config.HighWaterPercent, Config.LowWaterPercent,
        (long long)Config.MaxOutboundBytesPerSecond, (long long)Config.MaxInboundBytesPerSecond);
}

void FBVCTransportWorker::ApplyFlowConfig()
{
    if (!Flow.IsValid()) { return; }

    // 0 == unlimited; controller interprets as disabled for that direction.
    Flow->SetMaxOutboundBytesPerSecond(Config.MaxOutboundBytesPerSecond);
    Flow->SetMaxInboundBytesPerSecond(Config.MaxInboundBytesPerSecond);
}

bool FBVCTransportWorker::Init()
{
    return true;
}

uint32 FBVCTransportWorker::Run()
{
    // If the connection was already established before thread start, emit a state
    ConnectionStateWorker.Broadcast(Connection.IsConnected());

    while (!bStopRequested)
    {
        // Wait until we have something to do (inbound or outbound) or stop requested
        WakeEvent->Wait();

        if (bStopRequested)
        {
            break;
        }

        // Drain inbound first (keep latency low on reads)
        DrainInbound();

        // Then drain outbound
        DrainOutbound();

        // If more items arrived while draining, loop again without blocking
        bool bHasMore = false;
        {
            TArray<uint8> Dummy;
            if (InboundQueue.Peek(Dummy)) { bHasMore = true; }
        }
        {
            FOutbound Dummy;
            if (OutboundQueue.Peek(Dummy)) { bHasMore = true; }
        }
        if (bHasMore)
        {
            // Manually re-trigger the event to immediately continue
            WakeEvent->Trigger();
        }
    }

    return 0;
}

void FBVCTransportWorker::Stop()
{
    bStopRequested = true;
    if (WakeEvent) { WakeEvent->Trigger(); }
}

void FBVCTransportWorker::Send(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data)
{
    FOutbound Item;
    Item.ChannelId = ChannelId;
    Item.Priority  = Priority;
    Item.Payload   = TArray<uint8>(Data.GetData(), Data.Num());

    if (!OutboundQueue.TryEnqueue(MoveTemp(Item)))
    {
        MaybeLogOutboundDrop();
        MaybeWarnOutboundDepth();
        return;
    }

    // Re-evaluate backpressure immediately on the producer thread
    MaybeUpdateOutboundBackpressure();

    MaybeWarnOutboundDepth();

    if (WakeEvent) { WakeEvent->Trigger(); }
}

void FBVCTransportWorker::OnInboundFromTransport(const TArray<uint8>& WireBytes)
{
    // NOTE: We currently do NOT throttle inbound via Flow. The inbound bps limit is
    // kept in config (and sent to Flow) for future enhancements where we control
    // read cadence. For now, we accept frames as delivered by the transport.
    if (!InboundQueue.TryEnqueue(TArray<uint8>(WireBytes)))
    {
        MaybeLogInboundDrop();
        MaybeWarnInboundDepth();
        return;
    }

    // Re-evaluate backpressure immediately on the producer thread
    MaybeUpdateInboundBackpressure();

    MaybeWarnInboundDepth();

    if (WakeEvent) { WakeEvent->Trigger(); }
}

void FBVCTransportWorker::DrainInbound()
{
    int32 Count = 0;
    TArray<uint8> Bytes;

    while (!bStopRequested && Count < kMaxBatch && InboundQueue.Dequeue(Bytes))
    {
        EnvelopeReader.HandleInboundFrame(Bytes);
        ++Count;
    }

    // Backpressure maintenance for inbound (consumer-side confirmation)
    MaybeUpdateInboundBackpressure();
}

void FBVCTransportWorker::DrainOutbound()
{
    static thread_local FBVCMessageWriter Writer; // thread-confined to the worker

    int32 Count = 0;
    FOutbound Item;

    while (!bStopRequested && Count < kMaxBatch && OutboundQueue.Dequeue(Item))
    {
        // Build envelopes for this message
        const TArray<FBVCEnvelope> Envs =
            Writer.BuildMessage(Item.ChannelId, Item.Priority, Item.Payload);

        // Encode and send each envelope immediately
        for (const FBVCEnvelope& Env : Envs)
        {
            TArray<uint8> WireBytes;
            WireBytes.Reserve(BVC::Wire::kHeaderBytes + Env.Payload.Num());
            BVC::Wire::Encode(Env, WireBytes);

            // FLOW CONTROL: throttle based on configured outbound rate
            if (Flow.IsValid())
            {
                Flow->BeforeSend(WireBytes.Num());
            }

            Connection.SendBytes(WireBytes);
        }

        ++Count;
    }

    // Backpressure maintenance for outbound (consumer-side confirmation)
    MaybeUpdateOutboundBackpressure();
}

void FBVCTransportWorker::GetMetrics(FBVCWorkerMetrics& Out) const
{
    Out.InboundDepth  = InboundQueue.GetDepth();
    Out.InboundPeak   = 0; // reserved
    Out.InboundDrops  = InboundQueue.GetDrops();

    Out.OutboundDepth = OutboundQueue.GetDepth();
    Out.OutboundPeak  = 0; // reserved
    Out.OutboundDrops = OutboundQueue.GetDrops();

    Out.MaxOutboundBytesPerSecond = Config.MaxOutboundBytesPerSecond;
    Out.MaxInboundBytesPerSecond  = Config.MaxInboundBytesPerSecond;
}

void FBVCTransportWorker::MaybeWarnInboundDepth() const
{
    const int32 Cap   = InboundQueue.GetCapacity();
    const int32 Depth = InboundQueue.GetDepth();
    const int32 WarnT = PercentOf(Config.WarnPercent, Cap);
    if (WarnT > 0 && Depth >= WarnT)
    {
        UE_LOG(LogBVCWorker, VeryVerbose, TEXT("Inbound depth %d/%d (>= %d%%)"), Depth, Cap, Config.WarnPercent);
    }
}

void FBVCTransportWorker::MaybeWarnOutboundDepth() const
{
    const int32 Cap   = OutboundQueue.GetCapacity();
    const int32 Depth = OutboundQueue.GetDepth();
    const int32 WarnT = PercentOf(Config.WarnPercent, Cap);
    if (WarnT > 0 && Depth >= WarnT)
    {
        UE_LOG(LogBVCWorker, VeryVerbose, TEXT("Outbound depth %d/%d (>= %d%%)"), Depth, Cap, Config.WarnPercent);
    }
}

void FBVCTransportWorker::MaybeLogInboundDrop() const
{
    InboundDropsLogged++;
    const int32 Every = FMath::Max(1, Config.LogEveryNDrops);
    if ((InboundDropsLogged % Every) == 0)
    {
        UE_LOG(LogBVCWorker, Warning, TEXT("Inbound drops so far: %d (depth=%d/%d)"),
            InboundQueue.GetDrops(), InboundQueue.GetDepth(), InboundQueue.GetCapacity());
    }
}

void FBVCTransportWorker::MaybeLogOutboundDrop() const
{
    OutboundDropsLogged++;
    const int32 Every = FMath::Max(1, Config.LogEveryNDrops);
    if ((OutboundDropsLogged % Every) == 0)
    {
        UE_LOG(LogBVCWorker, Warning, TEXT("Outbound drops so far: %d (depth=%d/%d)"),
            OutboundQueue.GetDrops(), OutboundQueue.GetDepth(), OutboundQueue.GetCapacity());
    }
}

bool FBVCTransportWorker::IsInboundBackpressureActive() const
{
    const int32 Cap   = InboundQueue.GetCapacity();
    const int32 Depth = InboundQueue.GetDepth();
    const int32 High  = PercentOf(Config.HighWaterPercent, Cap);
    const int32 Low   = PercentOf(Config.LowWaterPercent,  Cap);

    // Hysteresis: once active, stays active until depth <= Low
    if (!bInboundBackpressured)
    {
        return Depth >= High;
    }
    else
    {
        return Depth > Low;
    }
}

bool FBVCTransportWorker::IsOutboundBackpressureActive() const
{
    const int32 Cap   = OutboundQueue.GetCapacity();
    const int32 Depth = OutboundQueue.GetDepth();
    const int32 High  = PercentOf(Config.HighWaterPercent, Cap);
    const int32 Low   = PercentOf(Config.LowWaterPercent,  Cap);

    if (!bOutboundBackpressured)
    {
        return Depth >= High;
    }
    else
    {
        return Depth > Low;
    }
}

void FBVCTransportWorker::MaybeUpdateInboundBackpressure() const
{
    const bool bNew = IsInboundBackpressureActive();
    if (bNew != bInboundBackpressured)
    {
        bInboundBackpressured = bNew;
        InboundBackpressureChanged.Broadcast(bInboundBackpressured);

        // Inform flow controller too (may influence shaping decisions)
        if (Flow.IsValid())
        {
            Flow->SetInboundBackpressure(bInboundBackpressured);
        }

        UE_LOG(LogBVCWorker, Log, TEXT("Inbound backpressure %s (depth=%d/%d, high=%d%% low=%d%%)"),
               bInboundBackpressured ? TEXT("ON") : TEXT("OFF"),
               InboundQueue.GetDepth(), InboundQueue.GetCapacity(),
               Config.HighWaterPercent, Config.LowWaterPercent);
    }
}

void FBVCTransportWorker::MaybeUpdateOutboundBackpressure() const
{
    const bool bNew = IsOutboundBackpressureActive();
    if (bNew != bOutboundBackpressured)
    {
        bOutboundBackpressured = bNew;
        OutboundBackpressureChanged.Broadcast(bOutboundBackpressured);

        // Inform flow controller too (may influence shaping decisions)
        if (Flow.IsValid())
        {
            Flow->SetOutboundBackpressure(bOutboundBackpressured);
        }

        UE_LOG(LogBVCWorker, Log, TEXT("Outbound backpressure %s (depth=%d/%d, high=%d%% low=%d%%)"),
               bOutboundBackpressured ? TEXT("ON") : TEXT("OFF"),
               OutboundQueue.GetDepth(), OutboundQueue.GetCapacity(),
               Config.HighWaterPercent, Config.LowWaterPercent);
    }
}
