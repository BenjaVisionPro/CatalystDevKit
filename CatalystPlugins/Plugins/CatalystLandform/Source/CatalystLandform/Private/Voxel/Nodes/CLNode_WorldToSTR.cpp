// Copyright (c) Catalyst
#include "Voxel/Nodes/CLNode_WorldToSTR.h"

void FVoxelNode_WorldToSTR::Compute(FVoxelGraphQuery Query) const
{
	// Unwrap (buffers by ref via TValue<>::operator*)
	const FVoxelDoubleVectorBuffer& World = *WorldPositionPin.Get(Query);

	// Unwrap scalars (TValue<double> -> double)
	const double CoreRadius = CoreRadiusMPin.Get(Query).Get();
	const double MaxHeight  = MaxHeightMPin.Get(Query).Get();

	const int32 Count = World.Num();

	// Allocate outputs
	FVoxelDoubleBuffer SBuf, TBuf, RBuf;
	SBuf.Allocate(Count);
	TBuf.Allocate(Count);
	RBuf.Allocate(Count);

	const FCLGeodesicConfig Cfg{ CoreRadius, MaxHeight };

	// IMPORTANT: read double components directly to avoid precision loss
	const FVoxelDoubleBuffer& X = World.X;
	const FVoxelDoubleBuffer& Y = World.Y;
	const FVoxelDoubleBuffer& Z = World.Z;

	for (int32 i = 0; i < Count; i++)
	{
		const FVector3d W( X[i], Y[i], Z[i] );

		double s, t, r;
		FCLGeodesicCoordinateSpace::WorldToSTR(W, Cfg, s, t, r);

		SBuf.Set(i, s);
		TBuf.Set(i, t);
		RBuf.Set(i, r);
	}

	// Push outputs
	SPin.Set(Query, SBuf);
	TPin.Set(Query, TBuf);
	RPin.Set(Query, RBuf);
}