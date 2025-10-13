// Copyright (c) Catalyst
#include "Voxel/Nodes/CLNode_STRToWorld.h"

void FVoxelNode_STRToWorld::Compute(FVoxelGraphQuery Query) const
{
	// Unwrap buffers (by ref)
	const FVoxelDoubleBuffer& SIn = *SPin.Get(Query);
	const FVoxelDoubleBuffer& TIn = *TPin.Get(Query);
	const FVoxelDoubleBuffer& RIn = *RPin.Get(Query);

	// Unwrap scalars
	const double CoreRadius = CoreRadiusMPin.Get(Query).Get();
	const double MaxHeight  = MaxHeightMPin.Get(Query).Get();

	// Broadcasting: operator[] handles constant buffers via IndexMask,
	// so we size by the max of input counts.
	const int32 Count = FMath::Max3(SIn.Num(), TIn.Num(), RIn.Num());

	// Prepare output buffer (allocate component double arrays)
	FVoxelDoubleVectorBuffer Out;
	Out.X.Allocate(Count);
	Out.Y.Allocate(Count);
	Out.Z.Allocate(Count);

	const FCLGeodesicConfig Cfg{ CoreRadius, MaxHeight };

	for (int32 i = 0; i < Count; i++)
	{
		const double s = SIn[i];
		const double t = TIn[i];
		const double r = RIn[i];

		const FVector3d W = FCLGeodesicCoordinateSpace::STRToWorld(s, t, r, Cfg);

		Out.X.Set(i, W.X);
		Out.Y.Set(i, W.Y);
		Out.Z.Set(i, W.Z);
	}

	WorldPositionPin.Set(Query, Out);
}