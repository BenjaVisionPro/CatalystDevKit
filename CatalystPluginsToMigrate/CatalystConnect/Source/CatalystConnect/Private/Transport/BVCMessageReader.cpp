// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCMessageReader.h"
#include "Containers/Array.h" // EAllowShrinking
#include "HAL/PlatformTime.h"
#include "Logging/LogMacros.h"

static constexpr uint8 kStartBit = 0x01;
static constexpr uint8 kEndBit   = 0x04;

FBVCMessageReader::FBVCMessageReader(FBVCChannelRegistry& InRegistry)
    : Registry(InRegistry)
{
}

void FBVCMessageReader::PushEnvelope(const FBVCEnvelope& Env)
{
    FBVCChannelState& State = Registry.GetOrCreate(Env.ChannelId);

    const bool bStart = (Env.Flags & kStartBit) != 0;
    const bool bEnd   = (Env.Flags & kEndBit)   != 0;

    // ----- Single-frame message (start+end) -----
    if (bStart && bEnd)
    {
        ScratchCompleted.Emplace(Env.Payload);
        const TArray<uint8>& Stable = ScratchCompleted.Last();

        FMessageView View;
        View.ChannelId = Env.ChannelId;
        View.Priority  = Env.Priority;
        View.MessageId = Env.MessageId;      // uint32
        View.Data      = Stable.Num() > 0 ? Stable.GetData() : nullptr; // allow nullptr for empty
        View.Size      = Stable.Num();

        checkf(View.Size >= 0 && (View.Size == 0 || View.Data != nullptr),
               TEXT("MessageReader produced an invalid view"));

        MessageReady.Broadcast(View);
        ScratchCompleted.Pop(EAllowShrinking::No); // keep pointer valid during Broadcast()
        return;
    }

    // ----- Multi-fragment path -----
    FBVCChannelState::FPartial& Partial = State.InFlight.FindOrAdd(Env.MessageId);
    if (Partial.Buffer.Num() == 0)
    {
        Partial.Total        = Env.TotalLength;
        Partial.NextSequence = 0;
    }

    // Strict in-order fragments
    if (Env.SequenceInMessage != Partial.NextSequence)
    {
        State.InFlight.Remove(Env.MessageId);
        return;
    }

    // Append this fragment
    Partial.Buffer.Append(Env.Payload);
    Partial.NextSequence++;
    Partial.LastTouchSeconds = FPlatformTime::Seconds();

    // Safety limits
    if (Partial.Buffer.Num() > MaxMessageBytes || Partial.Buffer.Num() > (int32)Partial.Total)
    {
        State.InFlight.Remove(Env.MessageId);
        return;
    }

    // Completed?
    if (bEnd && Partial.Buffer.Num() == (int32)Partial.Total)
    {
        ScratchCompleted.Emplace(MoveTemp(Partial.Buffer));
        const TArray<uint8>& Stable = ScratchCompleted.Last();

        FMessageView View;
        View.ChannelId = Env.ChannelId;
        View.Priority  = Env.Priority;
        View.MessageId = Env.MessageId;  // uint32
        View.Data      = Stable.Num() > 0 ? Stable.GetData() : nullptr; // allow nullptr for empty
        View.Size      = Stable.Num();

        checkf(View.Size >= 0 && (View.Size == 0 || View.Data != nullptr),
               TEXT("MessageReader produced an invalid view"));

        MessageReady.Broadcast(View);

        ScratchCompleted.Pop(EAllowShrinking::No);
        State.InFlight.Remove(Env.MessageId);
    }
}

void FBVCMessageReader::GarbageCollectTimedOut(double NowSeconds)
{
    Registry.ForEachState([&](uint16 /*ChannelId*/, FBVCChannelState& State)
    {
        auto& Map = State.InFlight;
        TArray<uint32> ToRemove; // u32 keys
        for (auto& It : Map)
        {
            if (NowSeconds - It.Value.LastTouchSeconds > FragmentTimeoutSeconds)
            {
                ToRemove.Add(It.Key);
            }
        }
        for (const uint32 G : ToRemove)
        {
            Map.Remove(G);
        }
    });
}
