#pragma once

#include "CoreMinimal.h"
#include "VoxelNode.h"
#include "Model/CLModelAsset.h"
#include "CLNode_GetCLModel.generated.h"

USTRUCT(Category = "Catalyst|Model")
struct CATALYSTLANDFORM_API FVoxelNode_GetCLModel : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Select the model asset on the node (no pin)
	UPROPERTY(EditAnywhere, Category="Catalyst|Model")
	TObjectPtr<UCLModelAsset> ModelAsset = nullptr;

	// Outputs (uniform doubles)
	VOXEL_OUTPUT_PIN(double, VoxelWorldRadiusM);
	VOXEL_OUTPUT_PIN(double, VoxelWorldHeightM);

	virtual void Compute(FVoxelGraphQuery Query) const override;
};