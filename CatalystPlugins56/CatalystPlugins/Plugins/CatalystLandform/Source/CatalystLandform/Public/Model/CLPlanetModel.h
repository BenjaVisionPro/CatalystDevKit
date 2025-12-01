// ============================================
// Catalyst Landform - Planet Model
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "CLPlanetModel.generated.h"

/**
 * Planet model for a landform. Units are meters.
 *
 * The playable shell is the spherical region between:
 *   Inner radius  = VoxelWorldRadiusM - VoxelWorldHeightM
 *   Outer radius  = VoxelWorldRadiusM
 *
 * Surface/atmosphere/etc. all live within that shell; strata are defined in
 * normalized altitude (0..1 of shell thickness).
 */
USTRUCT(BlueprintType)
struct CATALYSTLANDFORM_API FCLPlanetModel
{
	GENERATED_BODY()

	/** Absolute outer bound of the world (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Planet", meta=(Units="m", ClampMin="1"))
	double VoxelWorldRadiusM = 1000.0;

	/** Thickness of the playable shell (meters). Must be <= VoxelWorldRadiusM. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Planet", meta=(Units="m", ClampMin="1"))
	double VoxelWorldHeightM = 500.0;

	/** Clamp to sane ranges (call in asset normalize paths or before use). */
	void ClampModel()
	{
		VoxelWorldRadiusM = FMath::Max(1.0, VoxelWorldRadiusM);
		VoxelWorldHeightM = FMath::Clamp(VoxelWorldHeightM, 1.0, VoxelWorldRadiusM);
	}

	/** Lightweight validation (does not mutate). */
	bool IsValid() const
	{
		if (VoxelWorldRadiusM <= 0.0) return false;
		if (VoxelWorldHeightM <= 0.0) return false;
		if (VoxelWorldHeightM > VoxelWorldRadiusM) return false; // shell must fit inside outer radius
		return true;
	}

	/** Convenience helpers. */
	double GetInnerRadiusM() const
	{
		return FMath::Max(0.0, VoxelWorldRadiusM - VoxelWorldHeightM);
	}

	double GetOuterRadiusM() const
	{
		return VoxelWorldRadiusM;
	}
};