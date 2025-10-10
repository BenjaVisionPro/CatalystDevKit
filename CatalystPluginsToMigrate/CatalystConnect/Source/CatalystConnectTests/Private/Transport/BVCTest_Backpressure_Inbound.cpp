// ============================================
// Copyright © BenjaVision
// ============================================
// Verifies inbound backpressure hysteresis and single-toggle behavior.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Connection/UBVCConnectionManager.h"
#include "Transport/BVCTransportWorker.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_Backpressure_Inbound,
    "BVC.Backpressure.InboundHysteresis",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

static void PumpUntil(const TFunctionRef<bool()>& Pred, float Seconds=2.0f)
{
    const double End = FPlatformTime::Seconds() + Seconds;
    while (!Pred() && FPlatformTime::Seconds() < End)
    {
        // give the worker thread chance to run
        FPlatformProcess::Sleep(0.005f);
    }
}

bool FBVCTest_Backpressure_Inbound::RunTest(const FString&)
{
    // Real connection manager UObject
    UBVCConnectionManager* Conn = NewObject<UBVCConnectionManager>();

    // Standard reader chain
    FBVCChannelRegistry Channels;
    FBVCMessageReader   MsgReader(Channels);
    FBVCEnvelopeReader  EnvReader(MsgReader);

    // Worker
    FBVCTransportWorker Worker(*Conn, EnvReader, MsgReader);

    // Configure small capacity and hysteresis: High=50%, Low=25%
    FBVCTransportConfig Cfg;
    Cfg.InboundHardMaxItems  = 12;
    Cfg.OutboundHardMaxItems = 12;
    Cfg.HighWaterPercent     = 50;
    Cfg.LowWaterPercent      = 25;
    Cfg.WarnPercent          = 0;
    Cfg.LogEveryNDrops       = 1000;
    Worker.Configure(Cfg);

    // Track toggles
    int32 OnCount  = 0;
    int32 OffCount = 0;
    bool  bState   = false;

    auto Handle = Worker.OnInboundBackpressure().AddLambda([&](bool bActive)
    {
        bState = bActive;
        if (bActive) { ++OnCount; } else { ++OffCount; }
    });

    // Make a tiny frame
    TArray<uint8> Frame; Frame.AddUninitialized(8);

    // Push to exceed 50% of 12 => >=6 items
    for (int i=0; i<6; ++i)
    {
        Conn->OnInboundFrame().Broadcast(Frame);
    }

    PumpUntil([&]{ return OnCount >= 1; });

    TestEqual(TEXT("Inbound backpressure toggled ON exactly once"), OnCount, 1);
    TestTrue (TEXT("Inbound backpressure is active"), bState);

    // Now let the worker drain the queue by pumping a bit
    PumpUntil([&]{
        FBVCWorkerMetrics M{};
        Worker.GetMetrics(M);
        return M.InboundDepth <= (Cfg.LowWaterPercent * Cfg.InboundHardMaxItems) / 100;
    }, 2.0f);

    // Should toggle OFF once depth <= LowWater
    PumpUntil([&]{ return OffCount >= 1; });

    TestEqual(TEXT("Inbound backpressure toggled OFF exactly once"), OffCount, 1);
    TestFalse(TEXT("Inbound backpressure is inactive"), bState);

    Worker.OnInboundBackpressure().Remove(Handle);
    Worker.Stop(); // graceful shutdown

    return true;
}