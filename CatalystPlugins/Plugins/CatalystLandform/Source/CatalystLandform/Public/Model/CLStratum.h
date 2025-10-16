// ============================================================================
// CLStratum.h
// ============================================================================
#pragma once

#include "CoreMinimal.h"
#include "Model/CFObjectWithTitleAndComment.h"
#include "Model/CLTransition.h"
#include "CLStratum.generated.h"

/**
 * One horizontal shell (radial band) expressed in normalized altitude [0..1]
 * where 0 = inner/core surface, 1 = outer/sky bound.
 */
USTRUCT(BlueprintType)
struct CATALYSTLANDFORM_API FCLStratum : public FCFObjectWithTitleAndComment
{
	GENERATED_BODY()

	/** Start/end (inclusive) of this band, in normalized altitude [0..1]. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum", meta=(ClampMin="0.0", ClampMax="1.0"))
	double AltitudeMinN = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum", meta=(ClampMin="0.0", ClampMax="1.0"))
	double AltitudeMaxN = 1.0;

	/** Widths of the “fade in/out” ramps, as a fraction of this band’s span. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum", meta=(ClampMin="0.0", ClampMax="1.0"))
	double TransitionInN  = 0.0;   // ramp right above AltitudeMinN

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum", meta=(ClampMin="0.0", ClampMax="1.0"))
	double TransitionOutN = 0.0;   // ramp right below AltitudeMaxN

	/** Blend curve types for the ramps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum")
	ECLTransitionType TransitionInType  = ECLTransitionType::Smoothstep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Stratum")
	ECLTransitionType TransitionOutType = ECLTransitionType::Smoothstep;

	/** Lightweight validation (does not mutate). */
	bool IsValid() const
	{
		if (!(0.0 <= AltitudeMinN && AltitudeMinN <= 1.0)) return false;
		if (!(0.0 <= AltitudeMaxN && AltitudeMaxN <= 1.0)) return false;
		if (AltitudeMaxN <= AltitudeMinN) return false;

		const double Span = AltitudeMaxN - AltitudeMinN;
		if (TransitionInN  < 0.0 || TransitionOutN < 0.0) return false;
		if (TransitionInN  > 1.0 || TransitionOutN  > 1.0) return false;
		// Effective ramps cannot exceed the band span
		if (TransitionInN * Span + TransitionOutN * Span > Span + KINDA_SMALL_NUMBER) return false;
		return true;
	}

	/**
	 * Compute the weight [0..1] of this stratum at a given normalized altitude.
	 * Ramp-in is immediately above AltitudeMinN; ramp-out is immediately below AltitudeMaxN.
	 */
	double ComputeWeight(double AltitudeN) const;
};