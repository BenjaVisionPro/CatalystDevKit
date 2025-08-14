// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

// Include concrete types to avoid delete-incomplete issues with TUniquePtr in UHT .gen.cpp
#include "Transport/BVCChannelRegistry.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCTransportWorker.h"
#include "Transport/BVCMessageRouter.h"

#include "Connection/BVCConnectionConfig.h"

#include "UBVCConnection.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBVCConnection, Log, All);

class UBVCConnectionManager;

/**
 * UBVCConnection
 * Owns the per-connection pipeline:
 *   TransportWorker -> EnvelopeReader -> MessageReader -> MessageRouter
 * Surfaces router delegates for higher layers.
 */
UCLASS(BlueprintType)
class CATALYSTCONNECT_API UBVCConnection : public UObject
{
    GENERATED_BODY()

public:
    /** Build the pipeline with the given config (does not Connect). */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void InitializeConnection(const FBVCConnectionConfig& InConfig);

    /** Connect / Disconnect / IsConnected proxy to ConnectionManager. */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void Connect();

    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void Disconnect();

    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    bool IsConnected() const;

    /** Send a message (bytes already encoded as an envelope + message). */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void Send(int32 ChannelId, uint8 Priority, const TArray<uint8>& Bytes);

    /** Subscribe to messages via the router. */
    FBVCMessageRouter::FOnAnyMessage&     OnAnyMessage();
    FBVCMessageRouter::FOnChannelMessage& OnChannelMessage(uint16 ChannelId);

protected:
    virtual void BeginDestroy() override;

private:
    // Reader callback (worker thread): adapt to router view and route
    void HandleReaderMessage(const FBVCMessageReader::FMessageView& View);

private:
    UPROPERTY(Transient)
    TObjectPtr<UBVCConnectionManager> ConnectionManager = nullptr;

    // Pipeline
    TUniquePtr<FBVCChannelRegistry>   Channels;
    TUniquePtr<FBVCMessageReader>     Reader;
    TUniquePtr<FBVCEnvelopeReader>    EnvelopeReader;
    TUniquePtr<FBVCTransportWorker>   Worker;
    TUniquePtr<FBVCMessageRouter>     Router;

    // Config
    FBVCConnectionConfig              Config;
};
