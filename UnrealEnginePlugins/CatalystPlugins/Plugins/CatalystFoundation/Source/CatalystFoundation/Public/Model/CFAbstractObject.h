#pragma once
#include "CoreMinimal.h"
#include "CFAbstractObject.generated.h"

USTRUCT(BlueprintType)
struct FCFAbstractObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid Id = FGuid::NewGuid();

	void EnsureId()
	{
		if (!Id.IsValid())
		{
			Id = FGuid::NewGuid();
		}
	}
};