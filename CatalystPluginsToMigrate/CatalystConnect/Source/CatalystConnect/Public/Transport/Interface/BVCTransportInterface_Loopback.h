// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Transport/Interface/IBVCTransportInterface.h"

/**
 * FBVCTransportInterface_Loopback
 *
 * Simple in-process transport:
 *  - Connect/Disconnect only toggle state.
 *  - SendBytes(...) immediately re-emits the same bytes via OnInboundFrame().
 *
 * Useful for tests and editor workflows without real sockets.
 */
class CATALYSTCONNECT_API FBVCTransportInterface_Loopback final : public IBVCTransportInterface
{
public:
    FBVCTransportInterface_Loopback() = default;
    virtual ~FBVCTransportInterface_Loopback() override = default;

    // IBVCTransportInterface
    virtual void Connect(const FString& Url) override;
    virtual void Disconnect() override;
    virtual bool IsConnected() const override { return bConnected; }

    virtual void SendBytes(const TArray<uint8>& Bytes) override;
    virtual void Wake() override {} // nothing to wake in loopback

    virtual FBVCOnInboundFrame& OnInboundFrame() override { return Inbound; }
    virtual FString GetDebugName() const override { return TEXT("Loopback"); }

private:
    bool bConnected = false;
    FString LastUrl;

    FBVCOnInboundFrame Inbound;
};
