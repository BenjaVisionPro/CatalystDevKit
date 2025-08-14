#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UBVCStubGenerator.generated.h"
UCLASS() class UBVCStubGenerator : public UObject {
    GENERATED_BODY()
public: UFUNCTION(BlueprintCallable, Category="BVC|Codegen") void GenerateStubs() {}
};
