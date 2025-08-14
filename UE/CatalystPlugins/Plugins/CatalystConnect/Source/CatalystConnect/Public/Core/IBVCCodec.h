#pragma once
#include "CoreMinimal.h"
class IBVCCodec {
public: virtual ~IBVCCodec() = default;
    virtual FName GetName() const = 0; virtual FString GetMimeType() const = 0;
    virtual bool Encode(const TSharedRef<class FJsonObject>& InMessage, TArray<uint8>& OutBytes) = 0;
    virtual TSharedPtr<class FJsonObject> Decode(const TArray<uint8>& InBytes) = 0;
};
