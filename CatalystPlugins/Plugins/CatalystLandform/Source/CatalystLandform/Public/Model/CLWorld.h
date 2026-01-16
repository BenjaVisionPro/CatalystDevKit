#pragma once

#include "CoreMinimal.h"
#include "CLWorld.generated.h"

/**
 * CLWorld geometric band. Units are meters.
 *
 * OuterRadiusM: absolute outer bound of the voxel world.
 * WorldHeightM: shell thickness; valid altitude is [0..WorldHeightM] from inner radius.
 *
 * Strata are defined in normalized altitude (0..1 of shell thickness).
 */
USTRUCT(BlueprintType)
struct CATALYSTLANDFORM_API FCLWorld
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|World", meta=(Units="m", ClampMin="1"))
	double OuterRadiusM = 1000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|World", meta=(Units="m", ClampMin="1"))
	double WorldHeightM = 500.0;

	void ClampModel()
	{
		OuterRadiusM = FMath::Max(1.0, OuterRadiusM);
		WorldHeightM = FMath::Clamp(WorldHeightM, 1.0, OuterRadiusM);
	}

	bool IsValid() const
	{
		return OuterRadiusM > 0.0
			&& WorldHeightM > 0.0
			&& WorldHeightM <= OuterRadiusM;
	}

	double GetInnerRadiusM() const
	{
		return FMath::Max(0.0, OuterRadiusM - WorldHeightM);
	}
};