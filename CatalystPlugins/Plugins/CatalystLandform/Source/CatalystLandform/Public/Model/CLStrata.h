// ============================================================================
// CLStrata.h
// ============================================================================
#pragma once

#include "CoreMinimal.h"
#include "Model/CFObject.h"
#include "Model/CLStratum.h"
#include "CLStrata.generated.h"

/** One sample result: which stratum, and its weight. */
USTRUCT(BlueprintType)
struct CATALYSTLANDFORM_API FCLStratumSample
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Strata")
	FString StratumId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Strata")
	double WeightN = 0.0;
};

/**
 * A named collection of strata (radial bands).
 * Inherits its Catalyst identifier and label.
 */
USTRUCT(BlueprintType)
struct CATALYSTLANDFORM_API FCLStrata : public FCFLabelledObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Catalyst", meta=(MultiLine=true))
	FString Comment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Strata")
	TArray<FCLStratum> Strata;

	/** Validate all child strata. */
	bool IsValid() const
	{
		for (const FCLStratum& S : Strata)
		{
			if (!S.IsValid()) return false;
		}
		return true;
	}

	/**
	 * Gather all contributing strata at AltitudeN. If bNormalize, scales weights to sum to 1.
	 */
	void Sample(double AltitudeN, bool bNormalize, TArray<FCLStratumSample>& OutSamples) const;
};