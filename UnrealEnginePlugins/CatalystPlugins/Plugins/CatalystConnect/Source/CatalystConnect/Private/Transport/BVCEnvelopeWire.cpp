// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCEnvelopeWire.h"

namespace
{
    // --- write little-endian primitives ---
    FORCEINLINE void WriteU8 (TArray<uint8>& Out, uint8  V) { Out.Add(V); }
    FORCEINLINE void WriteU16(TArray<uint8>& Out, uint16 V)
    {
        Out.Add(static_cast<uint8>( V        & 0xFF));
        Out.Add(static_cast<uint8>((V >> 8 ) & 0xFF));
    }
    FORCEINLINE void WriteU32(TArray<uint8>& Out, uint32 V)
    {
        Out.Add(static_cast<uint8>( V         & 0xFF));
        Out.Add(static_cast<uint8>((V >>  8 ) & 0xFF));
        Out.Add(static_cast<uint8>((V >> 16 ) & 0xFF));
        Out.Add(static_cast<uint8>((V >> 24 ) & 0xFF));
    }

    // --- read little-endian primitives ---
    FORCEINLINE bool ReadU8 (const TArray<uint8>& In, int32& Off, uint8&  OutV)
    {
        if (Off + 1 > In.Num()) return false;
        OutV = In[Off++];
        return true;
    }
    FORCEINLINE bool ReadU16(const TArray<uint8>& In, int32& Off, uint16& OutV)
    {
        if (Off + 2 > In.Num()) return false;
        OutV =  static_cast<uint16>(In[Off])
              | static_cast<uint16>(In[Off+1] << 8);
        Off += 2;
        return true;
    }
    FORCEINLINE bool ReadU32(const TArray<uint8>& In, int32& Off, uint32& OutV)
    {
        if (Off + 4 > In.Num()) return false;
        OutV =   static_cast<uint32>(In[Off])
               | static_cast<uint32>(In[Off+1] << 8)
               | static_cast<uint32>(In[Off+2] << 16)
               | static_cast<uint32>(In[Off+3] << 24);
        Off += 4;
        return true;
    }
}

// -------- FBVCEnvelopeWire (single-envelope) -------------------------------

bool FBVCEnvelopeWire::Encode(const FBVCEnvelope& Env, TArray<uint8>& OutBytes)
{
    // Append (do NOT reset) so callers can build concatenated streams.
    const int32 Start = OutBytes.Num();
    OutBytes.Reserve(Start + BVC::Wire::kHeaderBytes + Env.Payload.Num());

    WriteU16(OutBytes, Env.ChannelId);
    WriteU8 (OutBytes, Env.Priority);
    WriteU8 (OutBytes, Env.Flags);
    WriteU32(OutBytes, Env.MessageId);          // uint32
    WriteU32(OutBytes, Env.TotalLength);
    WriteU16(OutBytes, Env.SequenceInMessage);
    WriteU32(OutBytes, static_cast<uint32>(Env.Payload.Num()));
    OutBytes.Append(Env.Payload);

    return true;
}

bool FBVCEnvelopeWire::Decode(const TArray<uint8>& InBytes, FBVCEnvelope& OutEnv)
{
    int32 Off = 0;

    uint16 ChannelId = 0;
    uint8  Priority  = 0;
    uint8  Flags     = 0;
    uint32 MsgId     = 0;
    uint32 Total     = 0;
    uint16 Seq       = 0;
    uint32 PayloadSz = 0;

    if (!ReadU16(InBytes, Off, ChannelId)) return false;
    if (!ReadU8 (InBytes, Off, Priority )) return false;
    if (!ReadU8 (InBytes, Off, Flags    )) return false;
    if (!ReadU32(InBytes, Off, MsgId    )) return false;
    if (!ReadU32(InBytes, Off, Total    )) return false;
    if (!ReadU16(InBytes, Off, Seq      )) return false;
    if (!ReadU32(InBytes, Off, PayloadSz)) return false;

    if (PayloadSz > static_cast<uint32>(InBytes.Num() - Off)) return false;

    OutEnv.ChannelId         = ChannelId;
    OutEnv.Priority          = Priority;
    OutEnv.Flags             = Flags;
    OutEnv.MessageId         = MsgId;     // uint32
    OutEnv.TotalLength       = Total;
    OutEnv.SequenceInMessage = Seq;

    OutEnv.Payload.SetNumUninitialized(static_cast<int32>(PayloadSz));
    if (PayloadSz > 0)
    {
        FMemory::Memcpy(OutEnv.Payload.GetData(), InBytes.GetData() + Off, PayloadSz);
    }

    return true;
}

FBVCEnvelope FBVCEnvelopeWire::MakeQuick(
    uint16 Channel, uint8 Priority, uint8 Flags, uint32 MsgId, uint32 Total, uint16 Seq, TArray<uint8> Payload)
{
    FBVCEnvelope E;
    E.ChannelId         = Channel;
    E.Priority          = Priority;
    E.Flags             = Flags;
    E.MessageId         = MsgId;
    E.TotalLength       = Total;
    E.SequenceInMessage = Seq;
    E.Payload           = MoveTemp(Payload);
    return E;
}

// -------- BVC::Wire (streaming adapter) ------------------------------------

void BVC::Wire::Encode(const FBVCEnvelope& Env, TArray<uint8>& Out)
{
    FBVCEnvelopeWire::Encode(Env, Out);
}

bool BVC::Wire::Decode(const TArray<uint8>& Bytes, int32& Offset, FBVCEnvelope& Out)
{
    if (Offset < 0 || Offset >= Bytes.Num())
    {
        return false;
    }

    int32 Off = Offset;

    // We can’t rely on the full header being there; check as we read.
    uint16 ChannelId = 0;
    uint8  Priority  = 0;
    uint8  Flags     = 0;
    uint32 MsgId     = 0;
    uint32 Total     = 0;
    uint16 Seq       = 0;
    uint32 PayloadSz = 0;

    if (!ReadU16(Bytes, Off, ChannelId)) return false;
    if (!ReadU8 (Bytes, Off, Priority )) return false;
    if (!ReadU8 (Bytes, Off, Flags    )) return false;
    if (!ReadU32(Bytes, Off, MsgId    )) return false;
    if (!ReadU32(Bytes, Off, Total    )) return false;
    if (!ReadU16(Bytes, Off, Seq      )) return false;
    if (!ReadU32(Bytes, Off, PayloadSz)) return false;

    // Ensure the payload fits in the remaining bytes
    if (PayloadSz > static_cast<uint32>(Bytes.Num() - Off))
    {
        return false; // incomplete frame
    }

    // Fill the out envelope
    Out.ChannelId         = ChannelId;
    Out.Priority          = Priority;
    Out.Flags             = Flags;
    Out.MessageId         = MsgId;
    Out.TotalLength       = Total;
    Out.SequenceInMessage = Seq;

    Out.Payload.SetNumUninitialized(static_cast<int32>(PayloadSz));
    if (PayloadSz > 0)
    {
        FMemory::Memcpy(Out.Payload.GetData(), Bytes.GetData() + Off, PayloadSz);
    }

    // Advance caller’s offset past this envelope
    Off += static_cast<int32>(PayloadSz);
    Offset = Off;
    return true;
}
