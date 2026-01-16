// Copyright © Catalyst

#include "CLVoxelWorldManager.h"

#include "VoxelWorld.h"
#include "VoxelInvalidationCallstack.h"

void FCLVoxelWorldManager::SetWorldRuntime(const AVoxelWorld& VoxelWorld, TSharedPtr<const FCLWorldRuntime> InWorldRuntime)
{
	VOXEL_FUNCTION_COUNTER();
	ensure(IsInGameThread());

	if (InWorldRuntime)
	{
		VoxelWorldToRuntime.Add(const_cast<AVoxelWorld*>(&VoxelWorld), MoveTemp(InWorldRuntime));
	}
	else
	{
		VoxelWorldToRuntime.Remove(const_cast<AVoxelWorld*>(&VoxelWorld));
	}

	FVoxelInvalidationScope Scope("FCLVoxelWorldManager::SetWorldRuntime");
	Dependency->Invalidate();
}

TSharedPtr<const FCLWorldRuntime> FCLVoxelWorldManager::GetWorldRuntime(const AVoxelWorld& VoxelWorld, FVoxelDependencyCollector& DependencyCollector) const
{
	ensure(IsInGameThread());
	DependencyCollector.AddDependency(*Dependency);
	return VoxelWorldToRuntime.FindRef(const_cast<AVoxelWorld*>(&VoxelWorld));
}