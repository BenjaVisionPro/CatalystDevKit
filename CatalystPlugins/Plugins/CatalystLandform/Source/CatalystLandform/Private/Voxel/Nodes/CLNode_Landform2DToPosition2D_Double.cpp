// Copyright © Catalyst

#include "Voxel/Nodes/CLNode_Landform2DToPosition2D_Double.h"
#include "VoxelGraphQuery.h"
#include "Voxel/FunctionLibraries/CLVoxelFunctionLibrary.h"

void FCLNode_Landform2DToPosition2D_Double::Compute(const FVoxelGraphQuery Query) const
{
	// Gather inputs
	const TValue<FVoxelDoubleVector2DBuffer> InLandform = Landform2DPin.Get(Query);
	const TValue<FVoxelDoubleBuffer>         InS        = SPin.Get(Query);
	const TValue<FVoxelDoubleBuffer>         InT        = TPin.Get(Query);
	const TValue<FVoxelDoubleBuffer>         InRm       = R_MPin.Get(Query);

	VOXEL_GRAPH_WAIT(InLandform, InS, InT, InRm)
	{
		TSharedRef<FVoxelDoubleVector2DBuffer> OutPos = MakeShared<FVoxelDoubleVector2DBuffer>();

		// Reverse transform (double path) – 6-arg signature (no overrides)
		UCLVoxelFunctionLibrary::Landform2DToPosition2D_Double(
			Query,
			*InLandform,
			*InS, *InT, *InRm,
			/*out*/ *OutPos);

		Position2DPin.Set(Query, OutPos);
	};
}