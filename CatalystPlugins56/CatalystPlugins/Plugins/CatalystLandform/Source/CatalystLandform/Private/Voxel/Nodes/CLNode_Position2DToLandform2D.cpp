// Copyright © Catalyst

#include "Voxel/Nodes/CLNode_Position2DToLandform2D.h"
#include "VoxelGraphQuery.h"
#include "VoxelBufferAccessor.h"
#include "Voxel/FunctionLibraries/CLVoxelFunctionLibrary.h"

void FCLNode_Position2DToLandform2D::Compute(const FVoxelGraphQuery Query) const
{
	const TValue<FVoxelVector2DBuffer> InPos     = Position2DPin.Get(Query);
	const TValue<double>               InInner   = InnerRadiusM_OverridePin.Get(Query);
	const TValue<double>               InHeight  = WorldHeightM_OverridePin.Get(Query);

	VOXEL_GRAPH_WAIT(InPos, InInner, InHeight)
	{
		// Convert input floats -> doubles for the library
		const int32 Count = InPos->Num();

		TSharedRef<FVoxelDoubleVector2DBuffer> PosD = MakeShared<FVoxelDoubleVector2DBuffer>();
		PosD->X.Allocate(Count);
		PosD->Y.Allocate(Count);
		for (int32 i = 0; i < Count; i++)
		{
			PosD->X.Set(i, static_cast<double>((*InPos).X[i]));
			PosD->Y.Set(i, static_cast<double>((*InPos).Y[i]));
		}

		// Prepare outputs from the double-precision path
		TSharedRef<FVoxelDoubleVector2DBuffer> Landform2D_D = MakeShared<FVoxelDoubleVector2DBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         S_D          = MakeShared<FVoxelDoubleBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         T_D          = MakeShared<FVoxelDoubleBuffer>();
		TSharedRef<FVoxelDoubleBuffer>         Rm_D         = MakeShared<FVoxelDoubleBuffer>();

		// NOTE: InInner/InHeight are plain doubles inside VOXEL_GRAPH_WAIT
		UCLVoxelFunctionLibrary::Position2DToLandform2D_Double(
			Query,
			*PosD,
			/*InnerRadius*/ InInner,
			/*WorldHeight*/ InHeight,
			/*out*/ *Landform2D_D,
			/*out*/ *S_D,
			/*out*/ *T_D,
			/*out*/ *Rm_D);

		// Write XY meters back to float buffer for Position
		TSharedRef<FVoxelVector2DBuffer> OutPosMeters = MakeShared<FVoxelVector2DBuffer>();
		OutPosMeters->X.Allocate(Count);
		OutPosMeters->Y.Allocate(Count);

		for (int32 i = 0; i < Count; i++)
		{
			OutPosMeters->X.Set(i, static_cast<float>(Landform2D_D->X[i]));
			OutPosMeters->Y.Set(i, static_cast<float>(Landform2D_D->Y[i]));
		}

		// Latitude/Longitude normalized (0..1) — use S/T directly as unitless
		TSharedRef<FVoxelFloatBuffer> OutLat = MakeShared<FVoxelFloatBuffer>();
		TSharedRef<FVoxelFloatBuffer> OutLon = MakeShared<FVoxelFloatBuffer>();
		OutLat->Allocate(Count);
		OutLon->Allocate(Count);

		for (int32 i = 0; i < Count; i++)
		{
			OutLat->Set(i, static_cast<float>((*S_D)[i]));
			OutLon->Set(i, static_cast<float>((*T_D)[i]));
		}

		// Altitude meters
		TSharedRef<FVoxelFloatBuffer> OutAltM = MakeShared<FVoxelFloatBuffer>();
		OutAltM->Allocate(Count);
		for (int32 i = 0; i < Count; i++)
		{
			OutAltM->Set(i, static_cast<float>((*Rm_D)[i]));
		}

		// Set outputs
		PositionPin.Set(Query, OutPosMeters);
		LatitudePin.Set(Query, OutLat);
		LongitudePin.Set(Query, OutLon);
		AltitudePin.Set(Query, OutAltM);
	};
}