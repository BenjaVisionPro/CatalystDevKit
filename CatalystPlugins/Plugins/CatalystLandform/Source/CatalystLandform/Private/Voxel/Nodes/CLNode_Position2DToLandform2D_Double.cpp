// Copyright © Catalyst

#include "Voxel/Nodes/CLNode_Position2DToLandform2D_Double.h"
#include "VoxelGraphQuery.h"
#include "Voxel/FunctionLibraries/CLVoxelFunctionLibrary.h"

void FCLNode_Position2DToLandform2D_Double::Compute(const FVoxelGraphQuery Query) const
{
	// Inputs
	const TValue<FVoxelDoubleVector2DBuffer> InPos    = Position2DPin.Get(Query);
	const TValue<double>                     InInner  = InnerRadiusM_OverridePin.Get(Query);
	const TValue<double>                     InHeight = WorldHeightM_OverridePin.Get(Query);

	VOXEL_GRAPH_WAIT(InPos, InInner, InHeight)
	{
		// Prepare outputs
		TSharedRef<FVoxelDoubleVector2DBuffer> OutLandform = MakeShared<FVoxelDoubleVector2DBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         OutS        = MakeShared<FVoxelDoubleBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         OutT        = MakeShared<FVoxelDoubleBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         OutR        = MakeShared<FVoxelDoubleBuffer>();

		// Core transform (double path)
		UCLVoxelFunctionLibrary::Position2DToLandform2D_Double(
			Query,
			*InPos,
			/*InnerRadius*/ InInner,
			/*WorldHeight*/ InHeight,
			/*out*/ *OutLandform,
			/*out*/ *OutS,
			/*out*/ *OutT,
			/*out*/ *OutR);

		// Set node outputs
		Landform2DPin.Set(Query, OutLandform);
		SPin.Set(Query, OutS);
		TPin.Set(Query, OutT);
		R_MPin.Set(Query, OutR);
	};
}