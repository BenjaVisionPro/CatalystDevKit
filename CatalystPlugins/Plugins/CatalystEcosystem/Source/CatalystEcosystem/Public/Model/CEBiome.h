// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObject.h"
#include "CEBiome.generated.h"

/** A biome groups animals and resources by environment (e.g., Desert, Tundra). */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEBiome : public FCFLabelledObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst", meta=(MultiLine=true))
	FString Comment;

	/** Optional loose links to other objects by identifier (keep model decoupled). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> ResourceIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> AnimalIds;
};