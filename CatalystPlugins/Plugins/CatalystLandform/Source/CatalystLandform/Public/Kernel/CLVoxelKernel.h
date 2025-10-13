#pragma once
#include "CoreMinimal.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"

struct FCLVoxelKernelConfig
{
	double CoreRadiusM = 1000.0;
	double MaxHeightM  = 500.0;
};

using FCLHeightFunction = TFunctionRef<double(double, double)>;
using FCLCaveFunction   = TFunctionRef<double(double, double, double)>;

struct FCLVoxelKernel
{
	static FORCEINLINE double SampleDensity_World(
		const FVector3d& WorldPos,
		const FCLVoxelKernelConfig& Cfg,
		FCLHeightFunction HeightFn,
		FCLCaveFunction CaveFn = DefaultCave)
	{
		double S, T, R;
		const FCLGeodesicConfig G{Cfg.CoreRadiusM, Cfg.MaxHeightM};
		FCLGeodesicCoordinateSpace::WorldToSTR(WorldPos, G, S, T, R);
		return SampleDensity_STR(S, T, R, Cfg, HeightFn, CaveFn);
	}

	static FORCEINLINE double SampleDensity_STR(
		double S, double T, double R,
		const FCLVoxelKernelConfig& Cfg,
		FCLHeightFunction HeightFn,
		FCLCaveFunction CaveFn = DefaultCave)
	{
		const double Height = HeightFn(S, T);
		const double Base   = Cfg.CoreRadiusM + Height;
		const double Cave   = CaveFn(S, T, R);
		return (R + Cave) - Base;
	}

private:
	static double DefaultCave(double, double, double) { return 0.0; }
};