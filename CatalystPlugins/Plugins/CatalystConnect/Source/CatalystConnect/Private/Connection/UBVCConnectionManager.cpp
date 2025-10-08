// ============================================
// Copyright © BenjaVision
// ============================================
#include "Connection/UBVCConnectionManager.h"
#include "Logging/LogMacros.h"

#include "Transport/Interface/BVCTransportInterface_WebSocket.h"
#include "Transport/Interface/BVCTransportInterface_Tcp.h"
#include "Transport/Interface/BVCTransportInterface_Http.h"
#include "Transport/Interface/BVCTransportInterface_Loopback.h"

// Flow control
#include "Transport/FlowControl/BVCTokenBucketFlow.h"

DEFINE_LOG_CATEGORY(LogBVCConnectionManager);

// Minimal URL splitter (scheme://host[:port]/path?query#fragment)
// For loopback, host may be absent (e.g., "loopback://", "loopback:").
static bool SimpleUrlSplit(const FString& Url, FString& OutScheme, FString& OutHost, int32& OutPort)
{
    OutScheme.Empty(); OutHost.Empty(); OutPort = -1;

    int32 SchemeEnd;
    if (!Url.FindChar(TEXT(':'), SchemeEnd)) return false;
    OutScheme = Url.Left(SchemeEnd).ToLower();

    FString Remainder = Url.Mid(SchemeEnd + 1); // after ':'
    if (Remainder.StartsWith(TEXT("//")))
    {
        Remainder = Remainder.Mid(2);
    }

    // host[:port] until / ? #
    int32 Slash = INDEX_NONE, Q = INDEX_NONE, H = INDEX_NONE;
    Remainder.FindChar(TEXT('/'), Slash);
    Remainder.FindChar(TEXT('?'), Q);
    Remainder.FindChar(TEXT('#'), H);

    int32 Cut = Remainder.Len();
    if (Slash >= 0) Cut = FMath::Min(Cut, Slash);
    if (Q     >= 0) Cut = FMath::Min(Cut, Q);
    if (H     >= 0) Cut = FMath::Min(Cut, H);

    const FString HostPort = Remainder.Left(Cut);

    if (!HostPort.IsEmpty())
    {
        int32 Colon = INDEX_NONE;
        HostPort.FindChar(TEXT(':'), Colon);
        if (Colon >= 0)
        {
            OutHost = HostPort.Left(Colon);
            const FString PortStr = HostPort.Mid(Colon + 1);
            OutPort = FCString::Atoi(*PortStr);
        }
        else
        {
            OutHost = HostPort;
        }
    }

    // Host can be empty for loopback; otherwise we require it.
    const bool bHostRequired = !(OutScheme == TEXT("loopback"));
    return !OutScheme.IsEmpty() && (!bHostRequired || !OutHost.IsEmpty());
}

TSharedPtr<IBVCTransportInterface> UBVCConnectionManager::CreateTransportFromUrl(const FString& Url)
{
    FString Scheme, Host;
    int32 Port = -1;
    if (!SimpleUrlSplit(Url, Scheme, Host, Port))
    {
        UE_LOG(LogBVCConnectionManager, Error, TEXT("Invalid URL: %s"), *Url);
        return nullptr;
    }

    if (Scheme == TEXT("loopback"))
    {
        return MakeShared<FBVCTransportInterface_Loopback>();
    }
    if (Scheme == TEXT("ws") || Scheme == TEXT("wss"))
    {
        return MakeShared<FBVCTransportInterface_WebSocket>();
    }
    if (Scheme == TEXT("tcp"))
    {
        return MakeShared<FBVCTransportInterface_Tcp>();
    }
    if (Scheme == TEXT("http") || Scheme == TEXT("https"))
    {
        return MakeShared<FBVCTransportInterface_Http>();
    }

    UE_LOG(LogBVCConnectionManager, Error, TEXT("Unsupported scheme '%s' in URL: %s"), *Scheme, *Url);
    return nullptr;
}

void UBVCConnectionManager::HookTransportInbound()
{
    UnhookTransportInbound();
    if (TransportImpl.IsValid())
    {
        InboundHandle = TransportImpl->OnInboundFrame().AddLambda(
            [this](const TArray<uint8>& Bytes)
            {
                // NOTE: We currently do not throttle inbound frames here.
                // If/when we gate inbound, we’ll add pacing analogous to BeforeSend.
                InboundRelay.Broadcast(Bytes);
            });
    }
}

void UBVCConnectionManager::UnhookTransportInbound()
{
    if (TransportImpl.IsValid() && InboundHandle.IsValid())
    {
        TransportImpl->OnInboundFrame().Remove(InboundHandle);
        InboundHandle.Reset();
    }
}

void UBVCConnectionManager::Connect(const FString& Url)
{
    CurrentUrl = Url;

    // Recreate transport if missing or not connected.
    const bool bNeedNew = !TransportImpl.IsValid() || !TransportImpl->IsConnected();
    if (bNeedNew)
    {
        TransportImpl = CreateTransportFromUrl(Url);

        // Create flow controller if missing
        if (!FlowControl.IsValid())
        {
            FlowControl = MakeShared<FBVCTokenBucketFlow>();
        }
        // Apply current caps to the flow controller
        FlowControl->SetMaxOutboundBytesPerSecond(CurrentFlow.MaxOutboundBytesPerSecond);
        FlowControl->SetMaxInboundBytesPerSecond(CurrentFlow.MaxInboundBytesPerSecond);

        HookTransportInbound();
    }

    if (TransportImpl.IsValid())
    {
        UE_LOG(LogBVCConnectionManager, Log, TEXT("Connect(%s) via %s"),
               *Url, *TransportImpl->GetDebugName());
        TransportImpl->Connect(Url);
    }
}

void UBVCConnectionManager::Disconnect()
{
    if (!TransportImpl.IsValid())
    {
        return;
    }

    UE_LOG(LogBVCConnectionManager, Log, TEXT("Disconnect (%s)"), *TransportImpl->GetDebugName());
    TransportImpl->Disconnect();
    UnhookTransportInbound();
    TransportImpl.Reset();
}

void UBVCConnectionManager::SendBytes(const TArray<uint8>& Bytes)
{
    if (!TransportImpl.IsValid())
    {
        UE_LOG(LogBVCConnectionManager, Warning, TEXT("SendBytes dropped: no transport (len=%d)"), Bytes.Num());
        return;
    }

    if (FlowControl.IsValid())
    {
        FlowControl->BeforeSend(Bytes.Num());
    }

    TransportImpl->SendBytes(Bytes);
}

void UBVCConnectionManager::SetFlowRates(const FBVCFlowRates& Rates)
{
    CurrentFlow = Rates;

    if (!FlowControl.IsValid())
    {
        FlowControl = MakeShared<FBVCTokenBucketFlow>();
    }

    FlowControl->SetMaxOutboundBytesPerSecond(CurrentFlow.MaxOutboundBytesPerSecond);
    FlowControl->SetMaxInboundBytesPerSecond(CurrentFlow.MaxInboundBytesPerSecond);

    UE_LOG(LogBVCConnectionManager, Log, TEXT("Flow updated: Out=%lld Bps, In=%lld Bps"),
           (long long)CurrentFlow.MaxOutboundBytesPerSecond,
           (long long)CurrentFlow.MaxInboundBytesPerSecond);
}

void UBVCConnectionManager::BeginDestroy()
{
    UnhookTransportInbound();
    TransportImpl.Reset();
    FlowControl.Reset();
    Super::BeginDestroy();
}
