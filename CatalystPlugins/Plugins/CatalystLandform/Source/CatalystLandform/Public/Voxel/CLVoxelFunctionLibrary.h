// ============================================================================
// CLVoxelFunctionLibrary
// Exposes Catalyst:Landform coordinate helpers to VPP2 voxel graphs
// ============================================================================

#pragma once
#include "CoreMinimal.h"
#include "VoxelFunctionLibrary.h"
#include "CLVoxelFunctionLibrary.generated.h"

UCLASS()
class CATALYSTLANDFORM_API UCLVoxelFunctionLibrary : public UVoxelFunctionLibrary
{
	GENERATED_BODY()

public:
	// Thread-safe math only! No UObject/world access.

	UFUNCTION(Category="Catalyst|Landform", meta=(DisplayName="CL World→STR"))
	static void CL_WorldToSTR(
		FVector WorldPos,
		double CoreRadiusM,
		double MaxHeightM,
		double& S, double& T, double& R);

	UFUNCTION(Category="Catalyst|Landform", meta=(DisplayName="CL STR→World"))
	static FVector CL_STRToWorld(
		double S, double T, double R,
		double CoreRadiusM,
		double MaxHeightM);

	UFUNCTION(Category="Catalyst|Landform", meta=(DisplayName="CL Wrap S [0,1)"))
	static double CL_WrapS(double S);
};