// ============================================================================
// CLLandformKernel
// Seam-safe density evaluation using the geodesic coordinate space.
// No shaping here: height comes from a caller-provided function.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"

// Tunables for the kernel (planet scale, etc.)
struct FCLLandformKernelConfig
{
	double CoreRadiusM = 1000.0; // meters
	double MaxHeightM  = 500.0;  // meters
};

// Height function: returns height above core shell at (S,T).
// Can be negative (ocean) or >MaxHeightM if you wish.
using FCLHeightFunction = TFunctionRef<double(double /*S*/, double /*T*/)>;

// Optional cave density function: delta density at (S,T,R).
using FCLCaveFunction   = TFunctionRef<double(double /*S*/, double /*T*/, double /*R*/)>;

struct FCLLandformKernel
{
	// World-space query
	static FORCEINLINE double SampleDensity_World(
		const FVector3d& WorldPos,
		const FCLLandformKernelConfig& Cfg,
		FCLHeightFunction HeightFn,
		FCLCaveFunction CaveFn = DefaultCave)
	{
		double S, T, R;
		const FCLGeodesicConfig G{ Cfg.CoreRadiusM, Cfg.MaxHeightM };
		FCLGeodesicCoordinateSpace::WorldToSTR(WorldPos, G, S, T, R);
		return SampleDensity_STR(S, T, R, Cfg, HeightFn, CaveFn);
	}

	// STR-space query:
	// density = (R + CaveDelta) - (CoreRadius + Height(S,T))
	static FORCEINLINE double SampleDensity_STR(
		const double S, const double T, const double R,
		const FCLLandformKernelConfig& Cfg,
		FCLHeightFunction HeightFn,
		FCLCaveFunction CaveFn = DefaultCave)
	{
		const double Height = HeightFn(S, T);
		const double Base   = (Cfg.CoreRadiusM + Height);
		const double Cave   = CaveFn(S, T, R);
		return (R + Cave) - Base;
	}

private:
	static double DefaultCave(double, double, double) { return 0.0; }
};