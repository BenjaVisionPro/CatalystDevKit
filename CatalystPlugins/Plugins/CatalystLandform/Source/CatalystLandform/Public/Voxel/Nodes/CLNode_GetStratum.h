#pragma once

#include "CoreMinimal.h"
#include "VoxelNode.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataAsset.h"
#include "CLNode_GetStratum.generated.h"

/** How to locate the stratum inside the asset */
UENUM()
enum class ECLStratumLookupMode : uint8
{
	ByTitle,
	ByIndex
};

/**
 * Get a single stratum (by Title or by Index) from a UCLStrataAsset
 * and expose its fields directly as terminal pins.
 */
USTRUCT(Category="Catalyst|Strata")
struct CATALYSTLANDFORM_API FVoxelNode_GetStratum : public FVoxelNode
{
	GENERATED_BODY()
	GENERATED_VOXEL_NODE_BODY()

	// Asset selected on the node (uniform)
	UPROPERTY(EditAnywhere, Category="Catalyst|Strata")
	TObjectPtr<UCLStrataAsset> StrataAsset = nullptr;

	// Lookup mode
	UPROPERTY(EditAnywhere, Category="Catalyst|Strata")
	ECLStratumLookupMode Mode = ECLStratumLookupMode::ByTitle;

	// Used if Mode == ByTitle
	UPROPERTY(EditAnywhere, Category="Catalyst|Strata")
	FName Title = NAME_None;

	// Used if Mode == ByIndex
	UPROPERTY(EditAnywhere, Category="Catalyst|Strata", meta=(ClampMin="0"))
	int32 Index = 0;

	// Outputs (terminal pins only)
	VOXEL_OUTPUT_PIN(bool,   Found);
	VOXEL_OUTPUT_PIN(double, AltitudeMinN);
	VOXEL_OUTPUT_PIN(double, AltitudeMaxN);
	VOXEL_OUTPUT_PIN(double, TransitionInN);
	VOXEL_OUTPUT_PIN(double, TransitionOutN);
	VOXEL_OUTPUT_PIN(int32,  TransitionInType);   // ECLTransitionType -> int
	VOXEL_OUTPUT_PIN(int32,  TransitionOutType);  // ECLTransitionType -> int
	VOXEL_OUTPUT_PIN(FName,  OutTitle);
	VOXEL_OUTPUT_PIN(FGuid,  OutId);

	virtual void Compute(FVoxelGraphQuery Query) const override;
};