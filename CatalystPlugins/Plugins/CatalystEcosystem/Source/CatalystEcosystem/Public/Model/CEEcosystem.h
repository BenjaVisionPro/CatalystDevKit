// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObject.h"
#include "CEEcosystem.generated.h"

/**
 * An ecosystem is a curated package of biomes, animals, and resources
 * (e.g., "Earth", "Cattle Farm", "Barren Moon", "Mediterranean Coast").
 */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEEcosystem : public FCFLabelledObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst", meta=(MultiLine=true))
	FString Comment;

	/** Collections that compose this ecosystem (referenced by identifier). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> BiomeIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> AnimalIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> ResourceIds;
};