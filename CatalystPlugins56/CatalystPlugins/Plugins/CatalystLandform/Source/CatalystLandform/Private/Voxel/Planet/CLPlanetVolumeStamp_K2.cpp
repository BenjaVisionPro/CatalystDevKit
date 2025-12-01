#include "Voxel/Planet/CLPlanetVolumeStamp_K2.h"
#include "Voxel/Planet/CLPlanetVolumeStamp.h"
#include "Voxel/Planet/CLPlanetVolumeStampRef.h"
#include "Voxel/Planet/CLPlanetVolumeGraph.h"

void UCLPlanetVolumeStamp_K2::MakePlanetStamp(FCLPlanetModel PlanetModel, FCLPlanetVolumeStampRef& StampRef)
{
	FCLPlanetVolumeStamp Stamp;
	Stamp.PlanetModel = PlanetModel;
	StampRef = FCLPlanetVolumeStampRef::New(Stamp);
}