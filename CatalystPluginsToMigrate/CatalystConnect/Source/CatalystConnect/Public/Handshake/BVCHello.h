#pragma once
#include "CoreMinimal.h"

/**
 * Minimal hello/ack structures (binary/json defined by chosen pre-handshake serializer).
 * These are DTOs only; no transport coupling.
 */
struct FBVCHello
{
    uint8 Version = 1;
    TArray<uint8> SupportedCodecs;        // e.g., {0=json,1=msgpack}
    TArray<uint8> SupportedCompression;   // e.g., {0=none,1=gzip}
    TMap<FName, uint16> SuggestedChannels; // name -> id (optional)
};

struct FBVCHelloAck
{
    uint8 Version = 1;
    TMap<FName, uint16> FinalChannels;
    TMap<uint16, uint8>  ChannelCodec;      // id -> codec
    TMap<uint16, uint8>  ChannelCompression;// id -> compression
};
