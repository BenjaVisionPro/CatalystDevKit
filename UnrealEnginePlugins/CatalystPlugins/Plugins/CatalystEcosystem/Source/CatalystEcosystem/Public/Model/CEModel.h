// ============================================
// CE: Root struct for the Ecosystem plugin data
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CEBiome.h"
#include "Model/CEAnimal.h"
#include "Model/CEResource.h"
#include "Model/CEEcosystem.h"
#include "CEModel.generated.h"

USTRUCT(BlueprintType)
struct FCEModel
{
	GENERATED_BODY()

	/** Packaged “scenarios” that group biomes/species/resources (e.g. Earth, Barren Moon). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CE|Model")
	TArray<FCEEcosystem> Ecosystems;

	/** Biomes in strict ecological terms (e.g. Temperate Forest, Arctic Desert). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CE|Model")
	TArray<FCEBiome> Biomes;

	/** Species list (animals for now). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CE|Model")
	TArray<FCEAnimal> Animals;

	/** Resources relevant to simulation/gameplay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CE|Model")
	TArray<FCEResource> Resources;
};