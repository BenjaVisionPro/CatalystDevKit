#pragma once

#include "VoxelNode.h"
#include "VoxelPinType.h"

// Buffer types
#include "Buffer/VoxelIntegerBuffers.h" // FVoxelInt32Buffer
#include "Buffer/VoxelDoubleBuffers.h"  // FVoxelDoubleBuffer
#include "Buffer/VoxelNameBuffer.h"     // FVoxelNameBuffer

#include "Model/CLStrata.h"             // FCLStratum, FCLStratumSample, UCLStrataAsset
#include "CLNode_SampleStrata.generated.h"

USTRUCT()
struct CATALYSTLANDFORM_API FVoxelNode_SampleStrata final : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

public:
	// ===== Inputs =====
	// Buffer input requires a Default in this Voxel version: use nullptr
	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, AltitudeN, nullptr);
	VOXEL_INPUT_PIN(bool,               Normalize, false);
	// Provide Resolution (floor(WorldHeight / VoxelSize)) from the graph
	VOXEL_INPUT_PIN(int32,              Resolution, 0);

	// Asset to sample
	UPROPERTY(EditAnywhere, Category="Catalyst|Strata")
	const UCLStrataAsset* StrataAsset = nullptr;

	// ===== Outputs =====
	VOXEL_OUTPUT_PIN(FVoxelInt32Buffer,  StratumIndex);
	VOXEL_OUTPUT_PIN(FVoxelDoubleBuffer, StratumWeightN);
	VOXEL_OUTPUT_PIN(FVoxelNameBuffer,   StratumTitle);

	// Execution
	void Compute(const FVoxelGraphQuery Query) const;
};