// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/Interface/IBVCTransportInterface.h"

/** Placeholder HTTP/HTTPS transport (e.g., SSE/long-polling). */
class CATALYSTCONNECT_API FBVCTransportInterface_Http final : public IBVCTransportInterface
{
public:
    virtual void     Connect(const FString& Url) override;
    virtual void     Disconnect() override;
    virtual bool     IsConnected() const override { return bConnected; }
    virtual void     SendBytes(const TArray<uint8>& Bytes) override;
    virtual void     Wake() override {}
    virtual FBVCOnInboundFrame& OnInboundFrame() override { return Inbound; }
    virtual FString  GetDebugName() const override { return TEXT("HTTP"); }

private:
    FString            CurrentUrl;
    bool               bConnected = false;
    FBVCOnInboundFrame Inbound;
};
