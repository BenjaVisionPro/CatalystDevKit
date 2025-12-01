#pragma once
#include "CoreMinimal.h"
#include "Runtime/CLEnums.h"

/**
 * Runtime-immutable POD used by Voxel workers (no UObjects).
 * Built by UCLVoxelWorldComponent when you later wire that path,
 * or provided via override pins in graph nodes for early testing.
 */
struct CATALYSTLANDFORM_API FCLWorldGeneratorModel
{
	// --- Header / identity ---
	uint32  SchemaVersion     = 1;
	FGuid   SourceAssetGuid;        // Optional if your asset exposes one
	uint64  InputSignatureHash = 0; // Optional (asset+param hash)

	// --- Planet band (R == altitude) ---
	double  InnerRadiusM      = 1000.0;
	double  WorldHeightM      = 2000.0;

	// --- Coord space selection & params ---
	ECLCoordSpace CoordSpace  = ECLCoordSpace::Geodesic;
	double  SeamBlendWidth    = 0.001; // normalized S width near seam

	// --- Determinism / seeds ---
	uint32  Seed              = 0;

	// (Optional future) baked tables: keep as immutable shared arrays
	// TSharedPtr<const TArray<FCLProvinceDef>> Provinces;
	// TSharedPtr<const TArray<FCLStratumSample>> StrataSamples;
};