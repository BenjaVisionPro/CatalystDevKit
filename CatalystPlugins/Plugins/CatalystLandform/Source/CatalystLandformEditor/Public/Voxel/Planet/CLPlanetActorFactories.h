#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "CLPlanetActorFactories.generated.h"

/**
 * Factory that spawns a VoxelStampActor preconfigured with FCLPlanetVolumeStamp.
 * Registered into the Voxel placement category via DEFINE_VOXEL_PLACEABLE_ITEM_FACTORY.
 */
UCLASS(meta = (VoxelPlaceableItem))
class CATALYSTLANDFORMEDITOR_API UActorFactory_CLPlanetStampActor : public UActorFactory
{
	GENERATED_BODY()

public:
	UActorFactory_CLPlanetStampActor();

	// UActorFactory overrides
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;
};