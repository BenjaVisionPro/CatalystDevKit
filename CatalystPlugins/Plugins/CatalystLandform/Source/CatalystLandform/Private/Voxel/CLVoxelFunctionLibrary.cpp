#include "Voxel/CLVoxelFunctionLibrary.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"

void UCLVoxelFunctionLibrary::CL_WorldToSTR(
	FVector WorldPos,
	double CoreRadiusM,
	double MaxHeightM,
	double& S, double& T, double& R)
{
	const FCLGeodesicConfig Cfg{ CoreRadiusM, MaxHeightM };
	FCLGeodesicCoordinateSpace::WorldToSTR(FVector3d(WorldPos), Cfg, S, T, R);
}

FVector UCLVoxelFunctionLibrary::CL_STRToWorld(
	double S, double T, double R,
	double CoreRadiusM,
	double MaxHeightM)
{
	const FCLGeodesicConfig Cfg{ CoreRadiusM, MaxHeightM };
	return FVector(FCLGeodesicCoordinateSpace::STRToWorld(S, T, R, Cfg));
}

double UCLVoxelFunctionLibrary::CL_WrapS(double S)
{
	return FCLGeodesicCoordinateSpace::WrapS(S);
}