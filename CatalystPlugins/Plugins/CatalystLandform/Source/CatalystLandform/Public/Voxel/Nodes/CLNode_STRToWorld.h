// Copyright (c) Catalyst
#pragma once

#include "CoreMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"
#include "CLNode_STRToWorld.generated.h"

USTRUCT(Category = "Catalyst|Coords")
struct CATALYSTLANDFORM_API FVoxelNode_STRToWorld : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs — defaults must be inner uniform type for buffers
	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, S, 0.0);
	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, T, 0.0);
	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, R, 0.0);
	VOXEL_INPUT_PIN(double, CoreRadiusM, 1000.0);
	VOXEL_INPUT_PIN(double, MaxHeightM, 500.0);

	// Output
	VOXEL_OUTPUT_PIN(FVoxelDoubleVectorBuffer, WorldPosition);

	virtual void Compute(FVoxelGraphQuery Query) const override;
};