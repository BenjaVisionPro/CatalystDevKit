// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEBiome.generated.h"

/** A biome groups animals and resources by environment (e.g., Desert, Tundra). */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEBiome : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** Optional loose links to other objects by Id (keep model decoupled). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> ResourceIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> AnimalIds;
};