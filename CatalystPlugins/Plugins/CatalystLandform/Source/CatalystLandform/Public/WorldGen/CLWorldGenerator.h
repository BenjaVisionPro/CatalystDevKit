// ============================================================================
// CLWorldGenerator (optional C++ adapter)
// Bridges VPP2 -> Landform kernel when you want a pure C++ path (no graphs).
// Currently disabled until we wire to the VPP2 C++ generator interface.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Kernel/CLLandformKernel.h"

#if 0 // Enable when wiring to VPP2 C++ generator interface
// #include "VoxelMinimal.h" // or the relevant VPP2 generator headers

class FCLWorldGenerator /* : public <VPP2 C++ generator base> */
{
public:
	explicit FCLWorldGenerator(FCLLandformKernelConfig InCfg)
		: Cfg(InCfg)
	{}

	// Example signature — adjust to VPP2’s actual API when you wire it.
	// virtual double GetDensity(const FVector3d& P) const override
	double GetDensity(const FVector3d& P) const
	{
		auto HeightFn = [](double /*S*/, double /*T*/) -> double
		{
			// Placeholder: 0 height => surface exactly on core radius.
			return 0.0;
		};

		return FCLLandformKernel::SampleDensity_World(P, Cfg, HeightFn);
	}

private:
	FCLLandformKernelConfig Cfg;
};
#endif