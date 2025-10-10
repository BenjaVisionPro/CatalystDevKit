#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UBVCBlueprintFunctionLibrary.generated.h"
UCLASS() class UBVCBlueprintFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="BVC|RemoteObject") static bool GetStringField(class UBVCRemoteObject* Obj, FName Field, FString& Out);
};
