#pragma once

#include "VoxelMinimal.h"
#include "VoxelStampBlueprintFunctionLibrary.h"
#include "Model/CLPlanetModel.h"
#include "CLPlanetVolumeStampRef.h"
#include "CLPlanetVolumeStamp_K2.generated.h"

UCLASS()
class CATALYSTLANDFORM_API UCLPlanetVolumeStamp_K2 : public UVoxelStampBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Voxel|Stamp|CL Planet", DisplayName="Make CL Planet Volume Stamp")
	static void MakePlanetStamp(FCLPlanetModel PlanetModel, FCLPlanetVolumeStampRef& StampRef);
};