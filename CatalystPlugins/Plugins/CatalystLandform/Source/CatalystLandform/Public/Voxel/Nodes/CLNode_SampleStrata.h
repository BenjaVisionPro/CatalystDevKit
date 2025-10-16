#pragma once

#include "CoreMinimal.h"
#include "VoxelNode.h"
#include "Buffer/VoxelDoubleBuffers.h"

#include "Voxel/CLStratumSampleBuffer.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataAsset.h"
#include "CLNode_SampleStrata.generated.h"

USTRUCT(Category="Catalyst|Strata")
struct CATALYSTLANDFORM_API FVoxelNode_SampleStrata : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	UPROPERTY(EditAnywhere, Category="Catalyst|Strata")
	TObjectPtr<UCLStrataAsset> StrataAsset = nullptr;

	// Inputs (Altitude normalized 0..1)
	VOXEL_INPUT_PIN(FVoxelDoubleBuffer, AltitudeN, 0.0);
	VOXEL_INPUT_PIN(bool,               Normalize, false, AdvancedDisplay);

	// Output: (StratumId, WeightN) flat list
	VOXEL_OUTPUT_PIN(FCLStratumSampleBuffer, Samples);

	virtual void Compute(FVoxelGraphQuery Query) const override;

private:
	// Replace these with your real access paths:
	// WorldHeight from CLModelAsset->Model.VoxelWorldHeightM
	// VoxelSize  from VoxelWorld->VoxelSize
	static double GetWorldHeight_FromNodeContext(const FVoxelGraphQuery& Query);
	static double GetVoxelSize_FromNodeContext(const FVoxelGraphQuery& Query);
};