// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEAnimal.generated.h"

/** A species/animal entry. */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEAnimal : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	// Example placeholders for later simulation data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	float TypicalMassKg = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FGuid> PreferredBiomeIds;
};