// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/Interface/IBVCTransportInterface.h"

/**
 * Placeholder WebSocket transport.
 * NOTE: This is a stub that simply echoes SendBytes() back as inbound frames
 * until the real platform WS implementation is wired in.
 */
class CATALYSTCONNECT_API FBVCTransportInterface_WebSocket final : public IBVCTransportInterface
{
public:
    // IBVCTransportInterface
    virtual void     Connect(const FString& Url) override;
    virtual void     Disconnect() override;
    virtual bool     IsConnected() const override { return bConnected; }
    virtual void     SendBytes(const TArray<uint8>& Bytes) override;
    virtual void     Wake() override {}
    virtual FBVCOnInboundFrame& OnInboundFrame() override { return Inbound; }
    virtual FString  GetDebugName() const override { return TEXT("WebSocket"); }

private:
    FString            CurrentUrl;
    bool               bConnected = false;
    FBVCOnInboundFrame Inbound;
};
