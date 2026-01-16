// Copyright © Catalyst

#include "CLVoxelSubsystem.h"

#include "CLVoxelWorldManager.h"

void FCLVoxelSubsystem::LoadFromPrevious(FVoxelSubsystem& InPreviousSubsystem)
{
	FCLVoxelSubsystem& Previous = CastStructChecked<FCLVoxelSubsystem>(InPreviousSubsystem);
	WorldRuntime = MoveTemp(Previous.WorldRuntime);
	Previous.WorldRuntime.Reset();
}

void FCLVoxelSubsystem::Initialize()
{
	VOXEL_FUNCTION_COUNTER();

	FVoxelDependencyCollector DependencyCollector(STATIC_FNAME("FCLVoxelSubsystem"));
	ON_SCOPE_EXIT
	{
		DependencyTracker = Finalize(DependencyCollector);
	};

	const UWorld* World = GetConfig().World.Resolve();
	if (!ensure(World))
	{
		WorldRuntime.Reset();
		return;
	}

	const AVoxelWorld* VoxelWorld = GetConfig().VoxelWorld.Get();
	if (!ensure(VoxelWorld))
	{
		WorldRuntime.Reset();
		return;
	}

	const TSharedRef<FCLVoxelWorldManager> Manager = FCLVoxelWorldManager::Get(World);
	WorldRuntime = Manager->GetWorldRuntime(*VoxelWorld, DependencyCollector);
}

TSharedPtr<const FCLWorldRuntime> FCLVoxelSubsystem::GetWorldRuntime(FVoxelDependencyCollector& DependencyCollector) const
{
	const UWorld* World = GetConfig().World.Resolve();
	const AVoxelWorld* VoxelWorld = GetConfig().VoxelWorld.Get();
	if (!World || !VoxelWorld)
	{
		return WorldRuntime;
	}

	const TSharedRef<FCLVoxelWorldManager> Manager = FCLVoxelWorldManager::Get(World);
	return Manager->GetWorldRuntime(*VoxelWorld, DependencyCollector);
}