#pragma once

#include "VoxelMinimal.h"
#include "VoxelVolumeStamp.h"
#include "Model/CLPlanetModel.h"
#include "CLPlanetVolumeStamp.generated.h"

class UCLPlanetVolumeGraph;

// Optional authoring asset
UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLPlanetVolumeStampAsset : public UObject
{
	GENERATED_BODY()

public:
	// Volume graph used by this planet stamp (not executed yet)
	UPROPERTY(EditAnywhere, Category = "Planet")
	TObjectPtr<UCLPlanetVolumeGraph> Graph = nullptr;

	// Planet model driving radii, shell height, etc.
	UPROPERTY(EditAnywhere, Category = "Planet")
	FCLPlanetModel PlanetModel;

	// Toggle for generating a flat patch instead of default behavior
	UPROPERTY(EditAnywhere, Category = "Planet", meta = (DisplayName = "Generate Flat Patch"))
	bool bGenerateFlatPatch = false;
};

// Final stamp type must derive from FVoxelVolumeStamp
class CATALYSTLANDFORM_API FCLPlanetVolumeStamp final : public FVoxelVolumeStamp
{
public:
	FCLPlanetVolumeStamp();

public:
	// Authorable properties (mirrors the asset for now)
	TObjectPtr<UCLPlanetVolumeGraph> Graph = nullptr;
	FCLPlanetModel PlanetModel;

	// Switch that will control flat-patch behavior at runtime
	bool bGenerateFlatPatch = false;
};

// Runtime placeholder for future mapping work — currently a pass-through
class CATALYSTLANDFORM_API FCLPlanetVolumeStampRuntime : public FVoxelVolumeStampRuntime
{
public:
	explicit FCLPlanetVolumeStampRuntime(const FCLPlanetVolumeStamp& InStamp);

	// Stubbed; will later use PlanetModel / Graph to compute proper bounds
	virtual FVoxelBox GetLocalBounds() const override;

	// For now, always fully invalidate when the runtime changes
	virtual bool ShouldFullyInvalidate(
		const FVoxelStampRuntime& PreviousRuntime,
		TVoxelArray<FVoxelBox>& OutLocalBoundsToInvalidate) const override;

	// Bulk query application
	virtual void Apply(
		const FVoxelVolumeBulkQuery& Query,
		const FVoxelVolumeTransform& StampToQuery) const override;

	// Sparse query application
	virtual void Apply(
		const FVoxelVolumeSparseQuery& Query,
		const FVoxelVolumeTransform& StampToQuery) const override;

private:
	TObjectPtr<UCLPlanetVolumeGraph> Graph = nullptr;
	FCLPlanetModel PlanetModel;

	// Runtime copy of the switch
	bool bGenerateFlatPatch = false;
};