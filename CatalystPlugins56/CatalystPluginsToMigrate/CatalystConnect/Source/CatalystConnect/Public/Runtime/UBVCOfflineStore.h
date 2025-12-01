#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UBVCOfflineStore.generated.h"

UINTERFACE(BlueprintType)
class CATALYSTCONNECT_API UBVCOfflineStore : public UInterface
{
    GENERATED_BODY()
};

class CATALYSTCONNECT_API IBVCOfflineStore
{
    GENERATED_BODY() // <-- This generates a virtual destructor for you.

public:
    // No explicit destructor here!

    // Pure virtuals for implementers
    virtual bool SaveSnapshot(const FString& Key, const TArray<uint8>& Data) = 0;
    virtual bool LoadSnapshot(const FString& Key, TArray<uint8>& OutData) = 0;
};
