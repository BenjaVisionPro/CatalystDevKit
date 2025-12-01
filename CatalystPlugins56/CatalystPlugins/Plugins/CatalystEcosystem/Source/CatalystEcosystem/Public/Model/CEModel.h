// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "CEEcosystem.h"
#include "CEBiome.h"
#include "CEAnimal.h"
#include "CEResource.h"
#include "CEModel.generated.h"

/** Root struct of the CE plugin data model. */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEModel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FCEEcosystem> Ecosystems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FCEBiome> Biomes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FCEAnimal> Animals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FCEResource> Resources;
};