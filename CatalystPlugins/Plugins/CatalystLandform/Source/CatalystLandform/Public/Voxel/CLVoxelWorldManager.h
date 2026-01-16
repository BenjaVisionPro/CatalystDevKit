// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelDependency.h"

#include "Runtime/CLWorldRuntime.h"

/**
 * Per-UWorld manager for CLWorld runtime snapshots, keyed by AVoxelWorld.
 *
 * Mirrors the VPP Scatter pattern: an IVoxelWorldSubsystem holds live data and
 * exposes a dependency so voxel states can track invalidation correctly.
 */
class AVoxelWorld;

class CATALYSTLANDFORM_API FCLVoxelWorldManager : public IVoxelWorldSubsystem
{
public:
	GENERATED_VOXEL_WORLD_SUBSYSTEM_BODY(FCLVoxelWorldManager);

	/** Set (or clear) the runtime snapshot for the given VoxelWorld. */
	void SetWorldRuntime(const AVoxelWorld& VoxelWorld, TSharedPtr<const FCLWorldRuntime> InWorldRuntime);

	/** Get the runtime snapshot for the given VoxelWorld and add a dependency. */
	TSharedPtr<const FCLWorldRuntime> GetWorldRuntime(const AVoxelWorld& VoxelWorld, FVoxelDependencyCollector& DependencyCollector) const;

private:
	const TSharedRef<FVoxelDependency> Dependency = FVoxelDependency::Create("FCLVoxelWorldManager");

	// Updated on game thread by UCLVoxelWorldComponent.
	TVoxelMap<TVoxelObjectPtr<const AVoxelWorld>, TSharedPtr<const FCLWorldRuntime>> VoxelWorldToRuntime;
};