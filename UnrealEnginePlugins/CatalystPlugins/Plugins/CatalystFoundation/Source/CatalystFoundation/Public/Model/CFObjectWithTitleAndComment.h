#pragma once

#include "CoreMinimal.h"
#include "Model/CFAbstractObject.h"
#include "CFObjectWithTitleAndComment.generated.h"

/**
 * Common leaf used anywhere you need a titled/commented thing.
 * Inherits Id from FCFAbstractObject.
 */
USTRUCT(BlueprintType)
struct FCFObjectWithTitleAndComment : public FCFAbstractObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst|Model")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst|Model")
	FString Comment;
};