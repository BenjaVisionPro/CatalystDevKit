// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "CEAnimal.generated.h"

/**
 * A basic animal definition.
 */
USTRUCT(BlueprintType)
struct CATALYSTECOSYSTEM_API FCEAnimal : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** Optional classification (e.g., Herbivore, Carnivore) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ecosystem")
	FName Class;
};
