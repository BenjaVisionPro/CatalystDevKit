// Copyright © Catalyst

#include "Voxel/Nodes/CLNode_Landform2DToPosition2D.h"
#include "VoxelGraphQuery.h"
#include "VoxelBufferAccessor.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "Voxel/FunctionLibraries/CLVoxelFunctionLibrary.h"

void FCLNode_Landform2DToPosition2D::Compute(const FVoxelGraphQuery Query) const
{
	// Gather inputs (float path)
	const TValue<FVoxelVector2DBuffer> InLandform = Landform2DPin.Get(Query);
	const TValue<FVoxelFloatBuffer>    InS        = SPin.Get(Query);
	const TValue<FVoxelFloatBuffer>    InT        = TPin.Get(Query);
	const TValue<FVoxelFloatBuffer>    InRm       = R_MPin.Get(Query);

	VOXEL_GRAPH_WAIT(InLandform, InS, InT, InRm)
	{
		// Promote float buffers to double
		const FVoxelBufferAccessor Acc(*InLandform, *InS, *InT, *InRm);
		const int32 Count = Acc.Num();

		TSharedRef<FVoxelDoubleVector2DBuffer> Landform_D = MakeShared<FVoxelDoubleVector2DBuffer>();
		Landform_D->X.Allocate(Count);
		Landform_D->Y.Allocate(Count);

		TSharedRef<FVoxelDoubleBuffer> S_D  = MakeShared<FVoxelDoubleBuffer>();  S_D->Allocate(Count);
		TSharedRef<FVoxelDoubleBuffer> T_D  = MakeShared<FVoxelDoubleBuffer>();  T_D->Allocate(Count);
		TSharedRef<FVoxelDoubleBuffer> Rm_D = MakeShared<FVoxelDoubleBuffer>(); Rm_D->Allocate(Count);

		for (int32 i = 0; i < Count; i++)
		{
			Landform_D->X.Set(i, static_cast<double>((*InLandform).X[i]));
			Landform_D->Y.Set(i, static_cast<double>((*InLandform).Y[i]));
			S_D->Set(i, static_cast<double>((*InS)[i]));
			T_D->Set(i, static_cast<double>((*InT)[i]));
			Rm_D->Set(i, static_cast<double>((*InRm)[i]));
		}

		// Compute in double
		TSharedRef<FVoxelDoubleVector2DBuffer> OutPos_D = MakeShared<FVoxelDoubleVector2DBuffer>();
		UCLVoxelFunctionLibrary::Landform2DToPosition2D_Double(
			Query,
			*Landform_D,
			*S_D, *T_D, *Rm_D,
			/*out*/ *OutPos_D);

		// Demote to float for output
		TSharedRef<FVoxelVector2DBuffer> OutPos = MakeShared<FVoxelVector2DBuffer>();
		OutPos->X.Allocate(Count);
		OutPos->Y.Allocate(Count);

		for (int32 i = 0; i < Count; i++)
		{
			OutPos->X.Set(i, static_cast<float>(OutPos_D->X[i]));
			OutPos->Y.Set(i, static_cast<float>(OutPos_D->Y[i]));
		}

		Position2DPin.Set(Query, OutPos);
	};
}