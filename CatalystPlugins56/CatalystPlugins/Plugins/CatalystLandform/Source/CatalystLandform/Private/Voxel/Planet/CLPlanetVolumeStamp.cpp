#include "Voxel/Planet/CLPlanetVolumeStamp.h"
#include "Voxel/Planet/CLPlanetVolumeGraph.h"

FCLPlanetVolumeStamp::FCLPlanetVolumeStamp() = default;

// ----- Runtime (currently pass-through; flat patch to be implemented later) -----

FCLPlanetVolumeStampRuntime::FCLPlanetVolumeStampRuntime(const FCLPlanetVolumeStamp& InStamp)
	: Graph(InStamp.Graph)
	, PlanetModel(InStamp.PlanetModel)
	, bGenerateFlatPatch(InStamp.bGenerateFlatPatch)
{
}

FVoxelBox FCLPlanetVolumeStampRuntime::GetLocalBounds() const
{
	// TODO: Use PlanetModel to compute a proper local bounding box
	return FVoxelBox(); // stub
}

bool FCLPlanetVolumeStampRuntime::ShouldFullyInvalidate(
	const FVoxelStampRuntime& /*PreviousRuntime*/,
	TVoxelArray<FVoxelBox>& /*OutLocalBoundsToInvalidate*/) const
{
	// For now we always invalidate everything when this stamp changes
	return true;
}

void FCLPlanetVolumeStampRuntime::Apply(
	const FVoxelVolumeBulkQuery& /*Query*/,
	const FVoxelVolumeTransform& /*StampToQuery*/) const
{
	VOXEL_FUNCTION_COUNTER();

	// Development phase: explicit pass-through, regardless of switch.
	// The switch is plumbed so we can branch behavior later.
	if (!bGenerateFlatPatch)
	{
		// Pass-through: do not modify Query; leave previous layer data intact.
		return;
	}

	// TODO: When implementing flat patch, use PlanetModel/Graph here
	// to write into Query.Distances / Query.SurfaceTypes / Query.MetadataBuffers.
}

void FCLPlanetVolumeStampRuntime::Apply(
	const FVoxelVolumeSparseQuery& /*Query*/,
	const FVoxelVolumeTransform& /*StampToQuery*/) const
{
	VOXEL_FUNCTION_COUNTER();

	// Same semantics as bulk path: pass-through for now
	if (!bGenerateFlatPatch)
	{
		return;
	}

	// TODO: Sparse flat-patch sampling will go here.
}