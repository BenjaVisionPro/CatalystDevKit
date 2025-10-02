// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Transport/Interface/BVCTransportInterface_Loopback.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogBVCTransportLoopback, Log, All);

void FBVCTransportInterface_Loopback::Connect(const FString& Url)
{
    LastUrl    = Url;
    bConnected = true;
    UE_LOG(LogBVCTransportLoopback, Log, TEXT("Loopback connected to %s"), *Url);
}

void FBVCTransportInterface_Loopback::Disconnect()
{
    if (!bConnected)
    {
        return;
    }
    bConnected = false;
    UE_LOG(LogBVCTransportLoopback, Log, TEXT("Loopback disconnected"));
}

void FBVCTransportInterface_Loopback::SendBytes(const TArray<uint8>& Bytes)
{
    if (!bConnected)
    {
        UE_LOG(LogBVCTransportLoopback, Verbose, TEXT("Loopback dropping %d bytes (not connected)"), Bytes.Num());
        return;
    }

    // Immediately echo back on the same thread that called SendBytes.
    Inbound.Broadcast(Bytes);
}
