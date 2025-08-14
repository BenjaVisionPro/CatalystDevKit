// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"

/**
 * Owns a fully reassembled transport message.
 * Generic: transport does not interpret the payload.
 */
struct CATALYSTCONNECT_API FBVCMessage
{
    /** Logical channel. */
    int32   ChannelId = 0;

    /** Transport priority. */
    uint8   Priority = 0;

    /** Message correlation/id (preserved from envelopes). */
    FGuid   MessageId;

    /** Owning payload bytes. */
    TArray<uint8> Payload;
};