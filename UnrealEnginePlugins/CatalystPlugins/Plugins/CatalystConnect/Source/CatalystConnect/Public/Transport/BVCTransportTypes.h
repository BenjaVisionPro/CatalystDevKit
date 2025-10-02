#pragma once

#include "CoreMinimal.h"

/** Raw inbound wire bytes event, emitted by a transport implementation. */
DECLARE_MULTICAST_DELEGATE_OneParam(FBVCOnInboundFrame, const TArray<uint8>& /*WireBytes*/);