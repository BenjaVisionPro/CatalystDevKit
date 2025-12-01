#pragma once

#include "VoxelMinimal.h"
#include "CLPlanetVolumeStamp.h"
#include "VoxelVolumeStampRef.h"
#include "CLPlanetVolumeStampRef.generated.h"

USTRUCT(BlueprintType, DisplayName="CL Planet Volume Stamp")
struct CATALYSTLANDFORM_API FCLPlanetVolumeStampRef final : public FVoxelVolumeStampRef
{
	GENERATED_BODY()
	GENERATED_VOXEL_STAMP_REF_BODY(FCLPlanetVolumeStampRef, FCLPlanetVolumeStamp)
};

template<>
struct TStructOpsTypeTraits<FCLPlanetVolumeStampRef> : TStructOpsTypeTraits<FVoxelStampRef>
{
};

template<>
struct TVoxelStampRefImpl<FCLPlanetVolumeStamp>
{
	using Type = FCLPlanetVolumeStampRef;
};