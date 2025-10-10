// ============================================
// Copyright © BenjaVision
// ============================================
#include "Transport/Interface/BVCTransportInterface_Tcp.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogBVCTransportTCP, Log, All);

void FBVCTransportInterface_Tcp::Connect(const FString& Url)
{
    CurrentUrl = Url;
    bConnected = true;
    UE_LOG(LogBVCTransportTCP, Log, TEXT("[TCP] Connect %s"), *Url);
}

void FBVCTransportInterface_Tcp::Disconnect()
{
    if (!bConnected) return;
    bConnected = false;
    UE_LOG(LogBVCTransportTCP, Log, TEXT("[TCP] Disconnect"));
}

void FBVCTransportInterface_Tcp::SendBytes(const TArray<uint8>& Bytes)
{
    if (!bConnected)
    {
        UE_LOG(LogBVCTransportTCP, Warning, TEXT("[TCP] Send dropped (not connected), len=%d"), Bytes.Num());
        return;
    }

    // STUB loopback
    Inbound.Broadcast(Bytes);
}
