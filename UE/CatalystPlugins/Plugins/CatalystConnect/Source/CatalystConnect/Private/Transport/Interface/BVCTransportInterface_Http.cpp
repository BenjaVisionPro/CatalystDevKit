// ============================================
// Copyright © BenjaVision
// ============================================
#include "Transport/Interface/BVCTransportInterface_Http.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogBVCTransportHTTP, Log, All);

void FBVCTransportInterface_Http::Connect(const FString& Url)
{
    CurrentUrl = Url;
    bConnected = true;
    UE_LOG(LogBVCTransportHTTP, Log, TEXT("[HTTP] Connect %s"), *Url);
}

void FBVCTransportInterface_Http::Disconnect()
{
    if (!bConnected) return;
    bConnected = false;
    UE_LOG(LogBVCTransportHTTP, Log, TEXT("[HTTP] Disconnect"));
}

void FBVCTransportInterface_Http::SendBytes(const TArray<uint8>& Bytes)
{
    if (!bConnected)
    {
        UE_LOG(LogBVCTransportHTTP, Warning, TEXT("[HTTP] Send dropped (not connected), len=%d"), Bytes.Num());
        return;
    }

    // STUB loopback
    Inbound.Broadcast(Bytes);
}
