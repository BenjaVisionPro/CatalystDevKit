#include "Voxel/Planet/CLPlanetActorFactories.h"

#include "VoxelStampActor.h"
#include "VoxelStampComponent.h"
#include "VoxelSettings.h"
#include "VoxelWorld.h"
#include "VoxelPlaceableItemUtilities.h"

#include "Graphs/VoxelVolumeGraph.h"
#include "Graphs/VoxelVolumeGraphStamp.h"

UActorFactory_CLPlanetStampActor::UActorFactory_CLPlanetStampActor()
{
	// Label shown in the Place Actors panel for the factory-registered entry
	DisplayName   = INVTEXT("CL Planet Stamp");
	// The actor type actually spawned in the level
	NewActorClass = AVoxelStampActor::StaticClass();
}

bool UActorFactory_CLPlanetStampActor::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	// 1) Dragging from the Voxel Place Actors panel:
	//    AssetData will be the actor class to spawn (AVoxelStampActor).
	if (AssetData.GetAsset() == AVoxelStampActor::StaticClass())
	{
		return true;
	}

	// 2) No asset info: still allow (will spawn a planet stamp actor with a default planet stamp)
	const UClass* Class = AssetData.GetClass();
	if (!Class)
	{
		return true;
	}

	// 3) Dragging a VoxelVolumeGraph asset from the Content Browser:
	//    we also want to handle that and wire the graph into the stamp.
	return Class->IsChildOf<UVoxelVolumeGraph>();
}

void UActorFactory_CLPlanetStampActor::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);

	AVoxelStampActor& StampActor = *CastChecked<AVoxelStampActor>(NewActor);
	StampActor.LabelPrefix = {};

	FVoxelVolumeGraphStamp Stamp;
	Stamp.Graph = Cast<UVoxelVolumeGraph>(Asset);
	Stamp.Layer = GetDefault<UVoxelSettings>()->DefaultVolumeLayer.LoadSynchronous();
	Stamp.Priority = UVoxelStampComponent::GetNewStampPriority(NewActor->GetWorld(), Stamp);
	Stamp.StampSeed.Randomize();
	StampActor.SetStamp(Stamp);

	// Ensure the stamp component & preview update like VPP's own factory
	StampActor.GetStampComponent().PostEditChange();
	AVoxelWorld::CreateNewIfNeeded_EditorOnly(NewActor);
}

// Registers this factory as a Voxel placeable item (runs automatically on editor startup)
DEFINE_VOXEL_PLACEABLE_ITEM_FACTORY(UActorFactory_CLPlanetStampActor);
