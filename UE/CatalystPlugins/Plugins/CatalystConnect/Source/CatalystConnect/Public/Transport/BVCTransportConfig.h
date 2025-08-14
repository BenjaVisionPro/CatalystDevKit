// ============================================
// Copyright © BenjaVision
// ============================================
#pragma once

#include "CoreMinimal.h"

/**
 * FBVCTransportConfig
 * Hard/soft queue limits and logging thresholds for the worker.
 * All limits are item counts (envelopes for outbound, frames for inbound).
 */
struct CATALYSTCONNECT_API FBVCTransportConfig
{
    /** Max inbound frames kept before newest are dropped. */
    int32 InboundHardMaxItems  = 1024;

    /** Max outbound items kept before newest are dropped. */
    int32 OutboundHardMaxItems = 1024;

    /** Emit a warning when depth >= (WarnPercent% of hard max). Range 0..100. */
    int32 WarnPercent          = 80;

    /** If >0, log every Nth drop to avoid log spam. */
    int32 LogEveryNDrops       = 100;
};