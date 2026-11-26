// ============================================
// Copyright © 2022
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObject.h"
#include "CEResource.generated.h"

/** A resource item (water, timber, minerals, etc.). */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEResource : public FCFLabelledObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst", meta=(MultiLine=true))
	FString Comment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	FString Unit; // e.g., "m³", "t", "kg"
};