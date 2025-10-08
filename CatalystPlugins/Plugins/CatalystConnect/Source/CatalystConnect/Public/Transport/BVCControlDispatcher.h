#pragma once

#include "CoreMinimal.h"
#include "Transport/BVCProtocolIds.h"       // BVC::ECtrlType, BVC::ControlChannelId
#include "Transport/BVCMessageReader.h"     // inbound, emits whole messages
#include "Transport/BVCMessageWriter.h"     // outbound, builds envelopes from a blob
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCCodecRegistry.h"

/**
 * Listens on the Control channel (BVC::ControlChannelId), handles control
 * messages (Hello, SwitchCodec), and emits ready-to-send **wire bytes**
 * for responses via OnOutboundWire.
 *
 * Inbound:  FBVCMessageReader::OnMessageReady(FMessageView)
 * Outbound: FBVCMessageWriter::BuildMessage(...) -> TArray<FBVCEnvelope>
 *           BVC::Wire::Encode(envelope, outBytes) for each envelope
 */
class CATALYSTCONNECT_API FBVCControlDispatcher
{
public:
    /** Wire bytes that are ready to go to the socket/WebSocket. */
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutboundWire, const TArray<uint8>& /*WireBytes*/);
    FOnOutboundWire OnOutboundWire;

public:
    FBVCControlDispatcher(FBVCMessageReader& InReader,
                          FBVCMessageWriter& InWriter,
                          FBVCChannelRegistry& InChannels,
                          FBVCCodecRegistry& InCodecs);

    /** Helpers to build raw control payloads (if callers ever need them). */
    static TArray<uint8> MakeHello(uint8 ProposedCodecId);
    static TArray<uint8> MakeSwitchCodec(uint16 ChannelId, uint8 NewCodecId);

private:
    void HookReader();
    void OnMessage(const FBVCMessageReader::FMessageView& View);

    void HandleHello(const uint8* Data, int32 Size);
    void HandleSwitchCodec(const uint8* Data, int32 Size);

private:
    FBVCMessageReader&    Reader;
    FBVCMessageWriter&    Writer;
    FBVCChannelRegistry&  Channels;
    FBVCCodecRegistry&    Codecs;

    FDelegateHandle       ReaderHandle;
};
