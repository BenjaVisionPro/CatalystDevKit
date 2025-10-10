// ============================================
// Copyright © BenjaVision
// ============================================
#include "Connection/UBVCConnection.h"
#include "Connection/UBVCConnectionManager.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY(LogBVCConnection);

void UBVCConnection::InitializeConnection(const FBVCConnectionConfig& InConfig)
{
    Config = InConfig;

    if (!ConnectionManager)
    {
        ConnectionManager = NewObject<UBVCConnectionManager>(this);
    }

    // Build pipeline owned by this connection
    Channels       = MakeUnique<FBVCChannelRegistry>();
    Reader         = MakeUnique<FBVCMessageReader>(*Channels);
    EnvelopeReader = MakeUnique<FBVCEnvelopeReader>(*Reader);
    Router         = MakeUnique<FBVCMessageRouter>();

    // Reader emits messages (worker thread) -> route via router
    Reader->OnMessageReady().AddUObject(this, &UBVCConnection::HandleReaderMessage);

    // Start worker with its deps
    Worker = MakeUnique<FBVCTransportWorker>(*ConnectionManager, *EnvelopeReader, *Reader);
}

void UBVCConnection::Connect()
{
    if (!ConnectionManager)
    {
        UE_LOG(LogBVCConnection, Warning, TEXT("Connect called before InitializeConnection."));
        return;
    }
    ConnectionManager->Connect(Config.Url);
}

void UBVCConnection::Disconnect()
{
    if (ConnectionManager)
    {
        ConnectionManager->Disconnect();
    }
}

bool UBVCConnection::IsConnected() const
{
    return ConnectionManager ? ConnectionManager->IsConnected() : false;
}

void UBVCConnection::Send(int32 ChannelId, uint8 Priority, const TArray<uint8>& Bytes)
{
    if (!Worker.IsValid())
    {
        UE_LOG(LogBVCConnection, Warning, TEXT("Send dropped: worker not initialized"));
        return;
    }
    Worker->Send(static_cast<uint16>(ChannelId), Priority, Bytes);
}

// Use router's delegate types explicitly to avoid dependent-type issues
FBVCMessageRouter::FOnAnyMessage& UBVCConnection::OnAnyMessage()
{
    check(Router.IsValid());
    return Router->OnAny();
}

FBVCMessageRouter::FOnChannelMessage& UBVCConnection::OnChannelMessage(uint16 ChannelId)
{
    check(Router.IsValid());
    return Router->OnChannel(ChannelId);
}

void UBVCConnection::BeginDestroy()
{
    // Tear down in reverse dep order
    if (Reader.IsValid())
    {
        Reader->OnMessageReady().RemoveAll(this);
    }

    Worker.Reset();
    EnvelopeReader.Reset();
    Reader.Reset();
    Channels.Reset();
    Router.Reset();

    Super::BeginDestroy();
}

void UBVCConnection::HandleReaderMessage(const FBVCMessageReader::FMessageView& View)
{
    if (!Router.IsValid())
    {
        return;
    }

    // Adapt reader view to router view (no copy of payload)
    FBVCMessageView Routed{
        /*ChannelId*/ View.ChannelId,
        /*Priority*/  View.Priority,
        /*MessageId*/ View.MessageId,
        /*Data*/      View.Data,
        /*Size*/      View.Size
    };

    Router->Route(Routed);
}
