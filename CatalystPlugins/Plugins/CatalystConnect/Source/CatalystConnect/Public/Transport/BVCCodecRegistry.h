#pragma once
#include "CoreMinimal.h"

class IBVCCodec;

/** Simple id -> codec pointer map (pointer may be null for “identity”). */
class CATALYSTCONNECT_API FBVCCodecRegistry
{
public:
    void Register(uint8 CodecId, IBVCCodec* CodecPtr)
    {
        Codecs.Add(CodecId, CodecPtr);
    }

    bool IsRegistered(uint8 CodecId) const
    {
        return Codecs.Contains(CodecId);
    }

    uint8 GetDefaultCodecId() const
    {
        return DefaultCodecId;
    }

    IBVCCodec* Find(uint8 CodecId) const
    {
        if (IBVCCodec* const* Found = Codecs.Find(CodecId))
        {
            return *Found;
        }
        return nullptr;
    }

private:
    TMap<uint8, IBVCCodec*> Codecs;
    uint8 DefaultCodecId = 0; // 0 = identity/raw by convention
};
