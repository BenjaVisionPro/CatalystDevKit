// Copyright (c) Catalyst
#pragma once

#include "CoreMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"
#include "CLNode_WorldToSTR.generated.h"

USTRUCT(Category = "Catalyst|Coords")
struct CATALYSTLANDFORM_API FVoxelNode_WorldToSTR : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Inputs — default must be the inner (uniform) type for buffers
	VOXEL_INPUT_PIN(FVoxelDoubleVectorBuffer, WorldPosition, FVoxelDoubleVector()); // (0,0,0)
	VOXEL_INPUT_PIN(double, CoreRadiusM, 1000.0);
	VOXEL_INPUT_PIN(double, MaxHeightM, 500.0);

	// Outputs
	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, S);
	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, T);
	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, R);

	virtual void Compute(FVoxelGraphQuery Query) const override;
};