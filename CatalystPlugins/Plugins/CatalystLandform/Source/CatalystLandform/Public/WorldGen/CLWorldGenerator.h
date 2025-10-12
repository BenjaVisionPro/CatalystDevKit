// ============================================================================
// CLWorldGenerator (optional C++ adapter)
// If/when you want a pure C++ path (no graph), this bridges VPP2 -> kernel.
// For now it's a stub so the project compiles without VPP2 includes.
// ============================================================================

#pragma once
#include "CoreMinimal.h"
#include "Kernel/CLLandformKernel.h"

#if 0 /* Enable when wiring to VPP2 C++ generator interface */
// #include "VoxelMinimal.h"  // or the relevant VPP2 generator headers

class FCLWorldGenerator /* : public IVoxelSomething in VPP2 */
{
public:
	explicit FCLWorldGenerator(FCLLandformKernelConfig InCfg)
		: Cfg(InCfg)
	{}

	// Example signature — adjust to VPP2’s actual API when you wire it.
	// double GetDensity(const FVector3d& P) const override
	double GetDensity(const FVector3d& P) const
	{
		// Pass a height function. For now, return 0 so the surface is CoreRadius shell.
		auto HeightFn = [](double /*S*/, double /*T*/) -> double { return 0.0; };
		return FCLLandformKernel::SampleDensity_World(P, Cfg, HeightFn);
	}

private:
	FCLLandformKernelConfig Cfg;
};
#endif