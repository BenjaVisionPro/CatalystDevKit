#pragma once
#include "CoreMinimal.h"

namespace BVC
{
    // Well-known channel ids
    static constexpr uint16 ControlChannelId = 0;

    // Control message types
    enum class ECtrlType : uint8
    {
        Hello       = 1, // [Type][ProposedCodecId:u8]
        HelloAck    = 2, // [Type][AcceptedCodecId:u8]
        SwitchCodec = 3, // [Type][ChannelId:u16 LE][CodecId:u8]
        SwitchAck   = 4, // [Type][ChannelId:u16 LE][CodecId:u8]
    };
}
