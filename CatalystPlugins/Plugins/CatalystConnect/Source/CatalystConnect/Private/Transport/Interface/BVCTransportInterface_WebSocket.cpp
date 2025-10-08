// ============================================
// Copyright © BenjaVision
// ============================================
#include "Transport/Interface/BVCTransportInterface_WebSocket.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogBVCTransportWS, Log, All);

void FBVCTransportInterface_WebSocket::Connect(const FString& Url)
{
    CurrentUrl = Url;
    bConnected = true;
    UE_LOG(LogBVCTransportWS, Log, TEXT("[WS] Connect %s"), *Url);
}

void FBVCTransportInterface_WebSocket::Disconnect()
{
    if (!bConnected) return;
    bConnected = false;
    UE_LOG(LogBVCTransportWS, Log, TEXT("[WS] Disconnect"));
}

void FBVCTransportInterface_WebSocket::SendBytes(const TArray<uint8>& Bytes)
{
    if (!bConnected)
    {
        UE_LOG(LogBVCTransportWS, Warning, TEXT("[WS] Send dropped (not connected), len=%d"), Bytes.Num());
        return;
    }

    // STUB: loop back for now so pipeline continues to work in-editor.
    Inbound.Broadcast(Bytes);
}
