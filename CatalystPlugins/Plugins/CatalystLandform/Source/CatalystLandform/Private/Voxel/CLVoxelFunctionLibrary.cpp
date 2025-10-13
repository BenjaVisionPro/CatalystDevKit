#include "Voxel/CLVoxelFunctionLibrary.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"

void UCLVoxelFunctionLibrary::CL_WorldToSTR(
	const FVoxelDoubleVectorBuffer& WorldPos,
	double CoreRadiusM,
	double MaxHeightM,
	FVoxelDoubleBuffer& S,
	FVoxelDoubleBuffer& T,
	FVoxelDoubleBuffer& R)
{
	const FCLGeodesicConfig Cfg{ CoreRadiusM, MaxHeightM };
	const int32 Count = WorldPos.X.Num();

	S.SetNum(Count);
	T.SetNum(Count);
	R.SetNum(Count);

	for (int32 i = 0; i < Count; ++i)
	{
		FCLGeodesicCoordinateSpace::WorldToSTR(
			FVector3d(WorldPos.X[i], WorldPos.Y[i], WorldPos.Z[i]),
			Cfg,
			S[i], T[i], R[i]);
	}
}

void UCLVoxelFunctionLibrary::CL_STRToWorld(
	const FVoxelDoubleBuffer& S,
	const FVoxelDoubleBuffer& T,
	const FVoxelDoubleBuffer& R,
	double CoreRadiusM,
	double MaxHeightM,
	FVoxelDoubleVectorBuffer& OutWorldPos)
{
	const FCLGeodesicConfig Cfg{ CoreRadiusM, MaxHeightM };
	const int32 Count = S.Num();

	OutWorldPos.X.SetNum(Count);
	OutWorldPos.Y.SetNum(Count);
	OutWorldPos.Z.SetNum(Count);

	for (int32 i = 0; i < Count; ++i)
	{
		const FVector3d P = FCLGeodesicCoordinateSpace::STRToWorld(S[i], T[i], R[i], Cfg);
		OutWorldPos.X[i] = P.X;
		OutWorldPos.Y[i] = P.Y;
		OutWorldPos.Z[i] = P.Z;
	}
}