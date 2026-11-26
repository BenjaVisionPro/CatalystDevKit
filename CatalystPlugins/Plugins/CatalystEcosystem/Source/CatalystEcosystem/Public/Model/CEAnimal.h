// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObject.h"
#include "CEAnimal.generated.h"

/** A species/animal entry. */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEAnimal : public FCFLabelledObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst", meta=(MultiLine=true))
	FString Comment;

	// Example placeholders for later simulation data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	float TypicalMassKg = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	TArray<FString> PreferredBiomeIds;
};