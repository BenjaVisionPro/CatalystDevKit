// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEResource.generated.h"

/**
 * A basic resource definition (e.g., Water, Timber).
 */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEResource : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** Arbitrary tags for filtering/grouping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FName> Tags;
};
