// ============================================
// Copyright © BenjaVision
// ============================================
// Verifies outbound backpressure hysteresis and single-toggle behavior.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Connection/UBVCConnectionManager.h"
#include "Transport/BVCTransportWorker.h"
#include "Transport/BVCEnvelopeReader.h"
#include "Transport/BVCMessageReader.h"
#include "Transport/BVCChannelRegistry.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBVCTest_Backpressure_Outbound,
    "BVC.Backpressure.OutboundHysteresis",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

static void PumpUntil2(const TFunctionRef<bool()>& Pred, float Seconds=2.0f)
{
    const double End = FPlatformTime::Seconds() + Seconds;
    while (!Pred() && FPlatformTime::Seconds() < End)
    {
        FPlatformProcess::Sleep(0.005f);
    }
}

bool FBVCTest_Backpressure_Outbound::RunTest(const FString&)
{
    UBVCConnectionManager* Conn = NewObject<UBVCConnectionManager>();

    FBVCChannelRegistry Channels;
    FBVCMessageReader   MsgReader(Channels);
    FBVCEnvelopeReader  EnvReader(MsgReader);

    FBVCTransportWorker Worker(*Conn, EnvReader, MsgReader);

    FBVCTransportConfig Cfg;
    Cfg.InboundHardMaxItems  = 12;
    Cfg.OutboundHardMaxItems = 12;
    Cfg.HighWaterPercent     = 50;
    Cfg.LowWaterPercent      = 25;
    Cfg.WarnPercent          = 0;
    Cfg.LogEveryNDrops       = 1000;
    Worker.Configure(Cfg);

    int32 OnCount  = 0;
    int32 OffCount = 0;
    bool  bState   = false;

    auto Handle = Worker.OnOutboundBackpressure().AddLambda([&](bool bActive)
    {
        bState = bActive;
        if (bActive) { ++OnCount; } else { ++OffCount; }
    });

    // Build a payload and enqueue enough messages to exceed 50% of 12 => >=6
    TArray<uint8> Payload; Payload.AddUninitialized(32);

    for (int i=0; i<6; ++i)
    {
        Worker.Send(/*Channel*/3, /*Priority*/0, TArrayView<const uint8>(Payload));
    }

    PumpUntil2([&]{ return OnCount >= 1; });

    TestEqual(TEXT("Outbound backpressure toggled ON exactly once"), OnCount, 1);
    TestTrue (TEXT("Outbound backpressure is active"), bState);

    // Allow worker to drain outbound (it does so in its own Run loop)
    PumpUntil2([&]{
        FBVCWorkerMetrics M{};
        Worker.GetMetrics(M);
        return M.OutboundDepth <= (Cfg.LowWaterPercent * Cfg.OutboundHardMaxItems) / 100;
    }, 2.0f);

    PumpUntil2([&]{ return OffCount >= 1; });

    TestEqual(TEXT("Outbound backpressure toggled OFF exactly once"), OffCount, 1);
    TestFalse(TEXT("Outbound backpressure is inactive"), bState);

    Worker.OnOutboundBackpressure().Remove(Handle);
    Worker.Stop();

    return true;
}