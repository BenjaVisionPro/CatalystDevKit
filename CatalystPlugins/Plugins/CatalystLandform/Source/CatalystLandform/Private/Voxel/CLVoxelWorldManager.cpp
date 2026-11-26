// Copyright © Catalyst

#include "Voxel/CLVoxelWorldManager.h"

#include "VoxelWorld.h"
#include "VoxelInvalidationCallstack.h"

void FCLVoxelWorldManager::SetWorldRuntime(const AVoxelWorld& VoxelWorld, TSharedPtr<const FCLWorldRuntime> InWorldRuntime)
{
	VOXEL_FUNCTION_COUNTER();
	ensure(IsInGameThread());

	const TVoxelObjectPtr<const AVoxelWorld> Key(&VoxelWorld);
	if (InWorldRuntime)
	{
		VoxelWorldToRuntime.FindOrAdd(Key) = MoveTemp(InWorldRuntime);
	}
	else
	{
		VoxelWorldToRuntime.Remove(Key);
	}

	FVoxelInvalidationScope Scope("FCLVoxelWorldManager::SetWorldRuntime");
	Dependency->Invalidate();
}

TSharedPtr<const FCLWorldRuntime> FCLVoxelWorldManager::GetWorldRuntime(const AVoxelWorld& VoxelWorld, FVoxelDependencyCollector& DependencyCollector) const
{
	ensure(IsInGameThread());
	DependencyCollector.AddDependency(*Dependency);
	return VoxelWorldToRuntime.FindRef(TVoxelObjectPtr<const AVoxelWorld>(&VoxelWorld));
}
