#pragma once

#include "CoreMinimal.h"
#include "Model/CFAbstractObject.h"
#include "CFObjectWithTitleAndComment.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFObjectWithTitleAndComment : public FCFAbstractObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Comment;
};
