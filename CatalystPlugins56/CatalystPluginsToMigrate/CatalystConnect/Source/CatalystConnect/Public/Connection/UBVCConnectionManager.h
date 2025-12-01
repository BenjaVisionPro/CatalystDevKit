// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Transport/Interface/IBVCTransportInterface.h"
#include "Transport/FlowControl/IBVCFlowControl.h"
#include "UBVCConnectionManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBVCConnectionManager, Log, All);

/** Simple flow configuration for this connection (0 == unlimited). */
USTRUCT(BlueprintType)
struct FBVCFlowRates
{
    GENERATED_BODY()

    /** Max outbound throughput in bytes per second (0 = unlimited). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Flow")
    int64 MaxOutboundBytesPerSecond = 0;

    /** Max inbound throughput in bytes per second (0 = unlimited). Reserved. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BVC|Flow")
    int64 MaxInboundBytesPerSecond = 0;
};

/**
 * ConnectionManager
 * - Owns a single IBVCTransportInterface instance created from a URL
 * - Exposes OnInboundFrame() for workers to subscribe to
 * - Forwards SendBytes()/Connect()/Disconnect()
 * - Owns optional FlowControl (token bucket) for pacing
 */
UCLASS()
class CATALYSTCONNECT_API UBVCConnectionManager : public UObject
{
    GENERATED_BODY()
public:
    /** Connect using the given URL (loopback://, ws://, wss://, tcp://, http://, https://). */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void Connect(const FString& Url);

    /** Disconnect and tear down transport. */
    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    void Disconnect();

    UFUNCTION(BlueprintCallable, Category="BVC|Connection")
    bool IsConnected() const { return TransportImpl.IsValid() && TransportImpl->IsConnected(); }

    /** Outbound bytes to transport (pacing applied if flow control configured). */
    void SendBytes(const TArray<uint8>& Bytes);

    /** Subscribe to raw inbound frames. */
    FBVCOnInboundFrame& OnInboundFrame() { return InboundRelay; }

    // -------- Flow control API --------

    /** Update flow caps at runtime (0 == unlimited). */
    UFUNCTION(BlueprintCallable, Category="BVC|Flow")
    void SetFlowRates(const FBVCFlowRates& Rates);

    /** Current flow caps. */
    UFUNCTION(BlueprintCallable, Category="BVC|Flow")
    FBVCFlowRates GetFlowRates() const { return CurrentFlow; }

    /** Internal access for worker hooks (backpressure signals). */
    TSharedPtr<IBVCFlowControl> GetFlowControl() const { return FlowControl; }

protected:
    virtual void BeginDestroy() override;

private:
    // Choose transport from URL scheme; return nullptr if unsupported.
    TSharedPtr<IBVCTransportInterface> CreateTransportFromUrl(const FString& Url);

    // Re-broadcast inbound frames from transport to our own delegate (stable lifetime for listeners).
    void HookTransportInbound();
    void UnhookTransportInbound();

private:
    TSharedPtr<IBVCTransportInterface> TransportImpl;

    // Flow control (token-bucket pacing)
    TSharedPtr<IBVCFlowControl> FlowControl;
    FBVCFlowRates               CurrentFlow;

    FBVCOnInboundFrame InboundRelay;
    FDelegateHandle    InboundHandle;
    FString            CurrentUrl;
};
