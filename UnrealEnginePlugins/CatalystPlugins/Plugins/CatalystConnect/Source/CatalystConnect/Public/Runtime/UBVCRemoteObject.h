#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core/BVCValue.h"
#include "UBVCRemoteObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBVCPatched, const FGuid&, ObjectId);

UCLASS(BlueprintType)
class CATALYSTCONNECT_API UBVCRemoteObject : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category="BVC|RemoteObject")
    FGuid Id;

    UPROPERTY(BlueprintReadOnly, Category="BVC|RemoteObject")
    FName RemoteType;

    UFUNCTION(BlueprintCallable, Category="BVC|RemoteObject")
    bool GetStringField(FName Field, FString& Out) const;

    UFUNCTION(BlueprintCallable, Category="BVC|RemoteObject")
    bool SetStringField(FName Field, const FString& In);

    UPROPERTY(BlueprintAssignable, Category="BVC|RemoteObject")
    FBVCPatched OnRemotePatched;

private:
    // Internal value store. Not UPROPERTY to avoid recursion issues (FBVCValue contains containers of FBVCValue).
    TMap<FName, FBVCValue> Fields;
};
