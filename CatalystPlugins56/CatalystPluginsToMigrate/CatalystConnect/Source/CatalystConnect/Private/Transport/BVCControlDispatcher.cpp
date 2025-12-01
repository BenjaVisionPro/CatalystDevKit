// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCControlDispatcher.h"
#include "Transport/BVCEnvelopeWire.h"
#include "Logging/LogMacros.h"

namespace
{
    FORCEINLINE void WriteU8(TArray<uint8>& Buf, uint8 V)         { Buf.Add(V); }
    FORCEINLINE void WriteU16LE(TArray<uint8>& Buf, uint16 V)     { Buf.Add((uint8)( V & 0xFF)); Buf.Add((uint8)((V >> 8) & 0xFF)); }
}

FBVCControlDispatcher::FBVCControlDispatcher(FBVCMessageReader& InReader,
                                             FBVCMessageWriter& InWriter,
                                             FBVCChannelRegistry& InChannels,
                                             FBVCCodecRegistry& InCodecs)
    : Reader(InReader)
    , Writer(InWriter)
    , Channels(InChannels)
    , Codecs(InCodecs)
{
    HookReader();
}

void FBVCControlDispatcher::HookReader()
{
    if (ReaderHandle.IsValid())
    {
        Reader.OnMessageReady().Remove(ReaderHandle);
        ReaderHandle.Reset();
    }
    ReaderHandle = Reader.OnMessageReady().AddRaw(this, &FBVCControlDispatcher::OnMessage);
}

TArray<uint8> FBVCControlDispatcher::MakeHello(uint8 ProposedCodecId)
{
    TArray<uint8> Bytes;
    WriteU8(Bytes, (uint8)BVC::ECtrlType::Hello);
    WriteU8(Bytes, ProposedCodecId);
    return Bytes;
}

TArray<uint8> FBVCControlDispatcher::MakeSwitchCodec(uint16 ChannelId, uint8 NewCodecId)
{
    TArray<uint8> Bytes;
    WriteU8(Bytes, (uint8)BVC::ECtrlType::SwitchCodec);
    WriteU16LE(Bytes, ChannelId);
    WriteU8(Bytes, NewCodecId);
    return Bytes;
}

void FBVCControlDispatcher::OnMessage(const FBVCMessageReader::FMessageView& View)
{
    if (View.ChannelId != BVC::ControlChannelId || View.Data == nullptr || View.Size <= 0)
    {
        return;
    }

    const uint8 Type = View.Data[0];
    switch ((BVC::ECtrlType)Type)
    {
        case BVC::ECtrlType::Hello:       HandleHello(View.Data, View.Size);       break;
        case BVC::ECtrlType::SwitchCodec: HandleSwitchCodec(View.Data, View.Size); break;
        default:
            UE_LOG(LogTemp, Verbose, TEXT("ControlDispatcher: Unknown control type %u len=%d"), (uint32)Type, View.Size);
            break;
    }
}

void FBVCControlDispatcher::HandleHello(const uint8* Data, int32 Size)
{
    if (Size < 2) return;

    const uint8 Proposed = Data[1];
    const uint8 Accepted = Codecs.IsRegistered(Proposed) ? Proposed : Codecs.GetDefaultCodecId();

    // HelloAck
    TArray<uint8> Ack;
    WriteU8(Ack, (uint8)BVC::ECtrlType::HelloAck);
    WriteU8(Ack, Accepted);

    const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(BVC::ControlChannelId, /*Priority*/0, Ack);

    // Encode each envelope into one wire buffer
    TArray<uint8> WireBytes;
    WireBytes.Reserve(Envs.Num() * 64);
    for (const FBVCEnvelope& Env : Envs)
    {
        BVC::Wire::Encode(Env, WireBytes);
    }
    OnOutboundWire.Broadcast(WireBytes);
}

void FBVCControlDispatcher::HandleSwitchCodec(const uint8* Data, int32 Size)
{
    if (Size < 1 + 2 + 1) return;

    const uint16 Channel = (uint16)(Data[1] | (Data[2] << 8));
    const uint8  Codec   = Data[3];

    Channels.SetCodec(Channel, Codec);

    // SwitchAck
    TArray<uint8> Ack;
    WriteU8(Ack, (uint8)BVC::ECtrlType::SwitchAck);
    WriteU16LE(Ack, Channel);
    WriteU8(Ack, Codec);

    const TArray<FBVCEnvelope> Envs = Writer.BuildMessage(BVC::ControlChannelId, /*Priority*/0, Ack);

    TArray<uint8> WireBytes;
    WireBytes.Reserve(Envs.Num() * 64);
    for (const FBVCEnvelope& Env : Envs)
    {
        BVC::Wire::Encode(Env, WireBytes);
    }
    OnOutboundWire.Broadcast(WireBytes);
}
