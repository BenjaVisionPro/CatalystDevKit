// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CatalystPlugin.generated.h"

UCLASS(Blueprintable)
class CATALYSTCONNECT_API UCatalystPlugin : public UObject
{
    GENERATED_BODY()

public:
    UCatalystPlugin();

    // Example property
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
    FString MyCustomProperty;

    // Example function
    UFUNCTION(BlueprintCallable, Category="Custom")
    void MyCustomFunction();
    
private:
    
    bool bCatalystPluginsInitialized = false;
    TArray<UClass*> CatalystPlugins;
    
    void FindCatalystPlugins();
};
