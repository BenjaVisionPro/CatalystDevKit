// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEEcosystem.generated.h"

/**
 * An ecosystem is a top-level grouping of biomes, animals, and resources
 * representing a coherent environment (e.g., Earth, Cattle Farm, Barren Moon).
 * 
 * Each ecosystem references other model objects *by Id* only, keeping models
 * loosely coupled. Details of those objects live in their own lists.
 */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEEcosystem : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** The set of biomes that make up this ecosystem. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> BiomeIds;

	/** Optional: specific animals uniquely tied to this ecosystem. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> AnimalIds;

	/** Optional: resources specific to this ecosystem. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> ResourceIds;

	/** Optional: future extension for weather patterns, rules, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> WeatherIds;
};