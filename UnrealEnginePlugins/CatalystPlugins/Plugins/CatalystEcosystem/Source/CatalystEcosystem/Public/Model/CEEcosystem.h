// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEEcosystem.generated.h"

/**
 * An ecosystem is a curated package of biomes, animals, and resources
 * (e.g., "Earth", "Cattle Farm", "Barren Moon", "Mediterranean Coast").
 */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEEcosystem : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** Collections that compose this ecosystem (referenced by Id). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> BiomeIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> AnimalIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> ResourceIds;
};