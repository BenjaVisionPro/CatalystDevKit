#include "Voxel/Planet/CLPlanetActorFactories.h"

#include "VoxelStampActor.h"
#include "VoxelStampComponent.h"
#include "VoxelSettings.h"
#include "VoxelWorld.h"
#include "VoxelPlaceableItemUtilities.h"

#include "Voxel/Planet/CLPlanetVolumeGraph.h"
#include "Voxel/Planet/CLPlanetVolumeStamp.h"
#include "Voxel/Planet/CLPlanetVolumeStampRef.h"

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

	// 3) Dragging a CLPlanetVolumeGraph asset from the Content Browser:
	//    we also want to handle that and wire the graph into the stamp.
	return Class->IsChildOf<UCLPlanetVolumeGraph>();
}

static void CL_UpdateNewStampCommon(FVoxelStamp& Stamp, UWorld* World)
{
	if (FVoxelVolumeStamp* VolumeStamp = Stamp.As<FVoxelVolumeStamp>())
	{
		VolumeStamp->Layer = GetDefault<UVoxelSettings>()->DefaultVolumeLayer.LoadSynchronous();
	}

	Stamp.Priority = UVoxelStampComponent::GetNewStampPriority(World, Stamp);
	Stamp.StampSeed.Randomize();
}

void UActorFactory_CLPlanetStampActor::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);

	AVoxelStampActor& StampActor = *CastChecked<AVoxelStampActor>(NewActor);
	StampActor.LabelPrefix = {};

	// Build a planet volume stamp and, if we were given a graph asset, attach it
	if (UCLPlanetVolumeGraph* Graph = Cast<UCLPlanetVolumeGraph>(Asset))
	{
		FCLPlanetVolumeStamp Stamp;
		Stamp.Graph = Graph;

		CL_UpdateNewStampCommon(Stamp, NewActor->GetWorld());
		StampActor.SetStamp(Stamp);
	}
	else
	{
		FCLPlanetVolumeStamp Stamp;
		CL_UpdateNewStampCommon(Stamp, NewActor->GetWorld());
		StampActor.SetStamp(Stamp);
	}

	// Ensure the stamp component & preview update like VPP's own factory
	StampActor.GetStampComponent().PostEditChange();
	AVoxelWorld::CreateNewIfNeeded_EditorOnly(NewActor);
}

// Registers this factory as a Voxel placeable item (runs automatically on editor startup)
DEFINE_VOXEL_PLACEABLE_ITEM_FACTORY(UActorFactory_CLPlanetStampActor)