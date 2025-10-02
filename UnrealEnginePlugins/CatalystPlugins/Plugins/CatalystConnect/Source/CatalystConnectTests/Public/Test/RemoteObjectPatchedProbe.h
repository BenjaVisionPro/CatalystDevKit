#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RemoteObjectPatchedProbe.generated.h"

UCLASS()
class URemoteObjectPatchedProbe : public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY()
    bool bCalled = false;

    UPROPERTY()
    bool bWasGameThread = false;

    UFUNCTION()
    void OnPatched(const FGuid& Id) // <-- needs a real name for UHT
    {
        bCalled = true;
        bWasGameThread = IsInGameThread();
        // (Id is unused here, but keeping it matches the delegate signature)
    }
};
