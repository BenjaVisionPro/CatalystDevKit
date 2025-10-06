/**
 * @file CFObjectWithTitleAndComment.h
 * @brief CFObjectWithTitleAndComment.h for Catalyst Foundation.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

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
