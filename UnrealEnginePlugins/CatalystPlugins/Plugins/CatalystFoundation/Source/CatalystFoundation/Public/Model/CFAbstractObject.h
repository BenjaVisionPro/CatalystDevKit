#pragma once

#include "CoreMinimal.h"
#include "CFAbstractObject.generated.h"

/**
 * Base model node for all plugin model objects.
 * Keep this a USTRUCT so leaf types can inherit without UObject overhead.
 */
USTRUCT(BlueprintType)
struct FCFAbstractObject
{
	GENERATED_BODY()

	/** Stable identifier for this node in the model graph. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst|Model")
	FGuid Id = FGuid::NewGuid();

	// (Optional) Shared hooks you want all nodes to have later, e.g. validation, equality, etc.
	// bool IsValid(FString& OutWhy) const;
};