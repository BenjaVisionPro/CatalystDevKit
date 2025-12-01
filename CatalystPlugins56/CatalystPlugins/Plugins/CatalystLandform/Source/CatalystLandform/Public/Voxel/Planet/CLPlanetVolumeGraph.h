// Catalyst Landform - Volume Graph (stub, no mapping yet)
#pragma once

#include "VoxelMinimal.h"
#include "VoxelGraph.h"
#include "Model/CLPlanetModel.h"
#include "CLPlanetVolumeGraph.generated.h"

UCLASS(BlueprintType, meta=(AssetSubMenu="Graph"))
class CATALYSTLANDFORM_API UCLPlanetVolumeGraph : public UVoxelGraph
{
	GENERATED_BODY()
public:
	// Authoring parameters shared with the stamp (no-op for now)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Planet")
	FCLPlanetModel PlanetModel;

public:
	//~ Begin UVoxelGraph Interface
#if WITH_EDITOR
	virtual FFactoryInfo GetFactoryInfo() override;
#endif
	virtual UScriptStruct* GetOutputNodeStruct() const override;
	//~ End UVoxelGraph Interface
};