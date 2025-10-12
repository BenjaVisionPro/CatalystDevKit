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

// Caller-provided height function signature:
//   HeightMeters(S,T) -> height above core shell [0..MaxHeightM] (can be negative if you want)
using FCLHeightFunction = TFunctionRef<double(double /*S*/, double /*T*/)>;

// Optional cave density function signature:
//   CaveDeltaDensity(S,T,R) -> value to add/subtract to density (default 0)
using FCLCaveFunction = TFunctionRef<double(double /*S*/, double /*T*/, double /*R*/)>;

struct FCLLandformKernel
{
	// World-space query: compute density at WorldPos using provided height/cave functions
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

	// STR-space query: density = R - (CoreRadius + Height(S,T)) + CaveDelta(S,T,R)
	static FORCEINLINE double SampleDensity_STR(
		const double S, const double T, const double R,
		const FCLLandformKernelConfig& Cfg,
		FCLHeightFunction HeightFn,
		FCLCaveFunction CaveFn = DefaultCave)
	{
		const double Height = HeightFn(S, T);         // your graph/logic supplies this
		const double Base   = (Cfg.CoreRadiusM + Height);
		const double Cave   = CaveFn(S, T, R);        // optional; usually 0 for now
		return (R + Cave) - Base;
	}

private:
	static double DefaultCave(double, double, double) { return 0.0; }
};