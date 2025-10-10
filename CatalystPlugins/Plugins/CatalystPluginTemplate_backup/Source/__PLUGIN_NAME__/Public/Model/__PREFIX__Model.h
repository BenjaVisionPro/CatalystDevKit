// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "__PREFIX__Ecosystem.h"
#include "__PREFIX__Biome.h"
#include "__PREFIX__Animal.h"
#include "__PREFIX__Resource.h"
#include "__PREFIX__Model.generated.h"

/** Root struct of the CE plugin data model. */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API F__PREFIX__Model
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="__PREFIX__")
	TArray<F__PREFIX__Ecosystem> Ecosystems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="__PREFIX__")
	TArray<F__PREFIX__Biome> Biomes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="__PREFIX__")
	TArray<F__PREFIX__Animal> Animals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="__PREFIX__")
	TArray<F__PREFIX__Resource> Resources;
};