#pragma once
#include "CoreMinimal.h"
#include "Kernel/CLVoxelKernel.h"

struct FCLWorldGenerator
{
	explicit FCLWorldGenerator(FCLVoxelKernelConfig InCfg)
		: Cfg(InCfg) {}

	double GetDensity(const FVector3d& P) const
	{
		auto HeightFn = [](double, double){ return 0.0; };
		return FCLVoxelKernel::SampleDensity_World(P, Cfg, HeightFn);
	}

private:
	FCLVoxelKernelConfig Cfg;
};