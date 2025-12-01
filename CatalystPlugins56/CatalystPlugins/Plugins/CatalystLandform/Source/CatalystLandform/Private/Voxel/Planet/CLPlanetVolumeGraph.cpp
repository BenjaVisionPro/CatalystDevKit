#include "Voxel/Planet/CLPlanetVolumeGraph.h"

UScriptStruct* UCLPlanetVolumeGraph::GetOutputNodeStruct() const
{
	// TODO: return your concrete output node struct when wired.
	return nullptr;
}

#if WITH_EDITOR
UVoxelGraph::FFactoryInfo UCLPlanetVolumeGraph::GetFactoryInfo()
{
	UVoxelGraph::FFactoryInfo Info;

	Info.Category = "Volume";
	Info.Description = "Used by Catalyst Landfrom to create a planetary flat patch";

	// Optional: Template can be set later when you have an asset path.
	// Info.Template = LoadObject<UCLPlanetVolumeGraph>(nullptr, TEXT("/Your/Path.YourAsset"));

	return Info;
}
#endif