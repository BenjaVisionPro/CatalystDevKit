// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCMessageWriter.h"

#include "HAL/PlatformAtomics.h"
#include "Misc/ScopeTryLock.h"

// Bits must match reader expectations
static constexpr uint8 kStartBit = 0x01;
static constexpr uint8 kEndBit   = 0x04;

static TAtomic<uint32> GNextMsgId{1}; // start at 1; wrap will skip 0

uint32 FBVCMessageWriter::NextMessageId()
{
    uint32 NewId = (uint32)FPlatformAtomics::InterlockedIncrement((volatile int32*)&GNextMsgId);
    if (NewId == 0) // extremely unlikely wrap guard
    {
        NewId = (uint32)FPlatformAtomics::InterlockedIncrement((volatile int32*)&GNextMsgId);
    }
    return NewId;
}

// ----------------------------------- Build -----------------------------------

TArray<FBVCEnvelope> FBVCMessageWriter::BuildMessage(uint16 ChannelId, uint8 Priority, const uint8* Data, int32 Size) const
{
    TArray<FBVCEnvelope> Out;
    BuildInternal(ChannelId, Priority, NextMessageId(), Data, Size, Out);
    return Out;
}

TArray<FBVCEnvelope> FBVCMessageWriter::BuildMessage(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data) const
{
    return BuildMessage(ChannelId, Priority, Data.GetData(), Data.Num());
}

TArray<FBVCEnvelope> FBVCMessageWriter::BuildMessage(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Data) const
{
    return BuildMessage(ChannelId, Priority, Data.GetData(), Data.Num());
}

TArray<FBVCEnvelope> FBVCMessageWriter::BuildMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size) const
{
    TArray<FBVCEnvelope> Out;
    BuildInternal(ChannelId, Priority, MessageId, Data, Size, Out);
    return Out;
}

// ----------------------------------- Send ------------------------------------

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, const uint8* Data, int32 Size)
{
    const uint32 MessageId = NextMessageId();
    TArray<FBVCEnvelope> Envs;
    BuildInternal(ChannelId, Priority, MessageId, Data, Size, Envs);
    for (const FBVCEnvelope& E : Envs) { EnvelopeReady.Broadcast(E); }
}

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, TArrayView<const uint8> Data)
{
    SendMessage(ChannelId, Priority, Data.GetData(), Data.Num());
}

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Data)
{
    SendMessage(ChannelId, Priority, Data.GetData(), Data.Num());
}

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size)
{
    TArray<FBVCEnvelope> Envs;
    BuildInternal(ChannelId, Priority, MessageId, Data, Size, Envs);
    for (const FBVCEnvelope& E : Envs) { EnvelopeReady.Broadcast(E); }
}

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, TArrayView<const uint8> Data)
{
    SendMessage(ChannelId, Priority, MessageId, Data.GetData(), Data.Num());
}

void FBVCMessageWriter::SendMessage(uint16 ChannelId, uint8 Priority, uint32 MessageId, const TArray<uint8>& Data)
{
    SendMessage(ChannelId, Priority, MessageId, Data.GetData(), Data.Num());
}

// ----------------------------------- Core ------------------------------------

void FBVCMessageWriter::BuildInternal(uint16 ChannelId, uint8 Priority, uint32 MessageId, const uint8* Data, int32 Size, TArray<FBVCEnvelope>& Out) const
{
    const int32 Total = FMath::Max(0, Size);
    uint16 Sequence = 0;

    if (Total == 0)
    {
        FBVCEnvelope Env;
        Env.ChannelId         = ChannelId;
        Env.Priority          = Priority;
        Env.Flags             = kStartBit | kEndBit;
        Env.MessageId         = MessageId;
        Env.TotalLength       = 0;
        Env.SequenceInMessage = 0;
        // Empty payload
        Out.Add(MoveTemp(Env));
        return;
    }

    int32 Offset = 0;
    const int32 ChunkSize = FMath::Max(1, MaxFragmentPayload);

    while (Offset < Total)
    {
        const int32 Remaining = Total - Offset;
        const int32 Chunk     = FMath::Min(Remaining, ChunkSize);

        FBVCEnvelope Env;
        Env.ChannelId         = ChannelId;
        Env.Priority          = Priority;
        Env.MessageId         = MessageId;
        Env.TotalLength       = Total;
        Env.SequenceInMessage = Sequence;

        const bool bFirst = (Offset == 0);
        const bool bLast  = (Offset + Chunk >= Total);
        Env.Flags = (bFirst ? kStartBit : 0) | (bLast ? kEndBit : 0);

        Env.Payload.SetNumUninitialized(Chunk);
        FMemory::Memcpy(Env.Payload.GetData(), Data + Offset, Chunk);

        Out.Add(MoveTemp(Env));

        Offset   += Chunk;
        Sequence += 1;
    }
}
