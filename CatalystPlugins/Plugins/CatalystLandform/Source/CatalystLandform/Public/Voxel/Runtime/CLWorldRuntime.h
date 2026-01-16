#pragma once

#include "CoreMinimal.h"

#include "Model/CLStrata.h"
#include "Voxel/Runtime/CLEnums.h"

/**
 * Runtime-immutable data used by voxel worker threads (no UObjects).
 *
 * Conventions:
 *  - Suffix M = meters
 *  - Suffix N = normalized (typically [0..1])
 */
struct CATALYSTLANDFORM_API FCLWorldRuntime
{
	// --- Identity / versioning ---
	uint32 SchemaVersion = 1;
	FGuid  SourceAssetGuid;
	uint64 InputSignatureHash = 0;

	// --- World band (R == altitude) ---
	double InnerRadiusM = 1000.0;
	double WorldHeightM = 2000.0;

	// --- Coord space selection & params ---
	ECLCoordSpace CoordSpace = ECLCoordSpace::Geodesic;
	double SeamBlendWidthN = 0.001;

	// --- Determinism ---
	uint32 Seed = 0;

	// --- Strata ---
	// Stored as pure data for worker thread reads.
	FCLStrata Strata;

	// Optional: precomputed normalized strata samples over altitude.
	// Index is QuantizeAltitudeN(AltitudeN).
	int32 StrataLutResolution = 0;
	TArray<TArray<FCLStratumSample>> StrataLut;

	FORCEINLINE int32 QuantizeAltitudeN(const double AltitudeN) const
	{
		if (StrataLutResolution <= 0)
		{
			return 0;
		}

		const double T = FMath::Clamp(AltitudeN, 0.0, 1.0);
		return FMath::RoundToInt(T * double(StrataLutResolution));
	}

	FORCEINLINE const TArray<FCLStratumSample>* SampleStrataLut(const double AltitudeN) const
	{
		if (StrataLutResolution <= 0 || StrataLut.Num() == 0)
		{
			return nullptr;
		}

		const int32 Index = QuantizeAltitudeN(AltitudeN);
		return StrataLut.IsValidIndex(Index) ? &StrataLut[Index] : nullptr;
	}
};