// Copyright © Catalyst
#pragma once

#include "VoxelMinimal.h"
#include "VoxelSubsystem.h"

#include "Runtime/CLWorldRuntime.h"

#include "CLVoxelSubsystem.generated.h"

class FCLVoxelWorldManager;

/**
 * Catalyst Landform voxel subsystem.
 *
 * Auto-instantiated by VPP because it derives from FVoxelSubsystem.
 * Snapshots the current CLWorld runtime data from FCLVoxelWorldManager during Initialize(),
 * and exposes that snapshot (plus dependency correctness) to graph/stamp evaluation.
 */
USTRUCT()
struct CATALYSTLANDFORM_API FCLVoxelSubsystem : public FVoxelSubsystem
{
	GENERATED_BODY()
	GENERATED_VOXEL_SUBSYSTEM_BODY()

public:
	//~ Begin FVoxelSubsystem Interface
	virtual void LoadFromPrevious(FVoxelSubsystem& InPreviousSubsystem) override;
	virtual void Initialize() override;
	//~ End FVoxelSubsystem Interface

public:
	/**
	 * Get the current CLWorld runtime snapshot.
	 * Adds the manager dependency to the collector so VPP will invalidate correctly.
	 */
	TSharedPtr<const FCLWorldRuntime> GetWorldRuntime(FVoxelDependencyCollector& DependencyCollector) const;

private:
	TSharedPtr<FVoxelDependencyTracker> DependencyTracker;
	TSharedPtr<const FCLWorldRuntime> WorldRuntime;
};