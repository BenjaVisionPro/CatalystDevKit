#pragma once
#include "CoreMinimal.h"
class IBVCCompressor {
public: virtual ~IBVCCompressor() = default;
    virtual FName GetName() const = 0;
    virtual bool Compress(const TArray<uint8>& InRaw, TArray<uint8>& OutCompressed) = 0;
    virtual bool Decompress(const TArray<uint8>& InCompressed, TArray<uint8>& OutRaw) = 0;
};
