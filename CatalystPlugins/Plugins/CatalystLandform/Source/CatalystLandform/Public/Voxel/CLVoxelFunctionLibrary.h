#pragma once
#include "CoreMinimal.h"
#include "VoxelMinimal.h"
#include "VoxelBuffer.h"
#include "VoxelFunctionLibrary.h"
#include "CLVoxelFunctionLibrary.generated.h"

/**
 * Catalyst:Landform → VPP2 adapter.
 * No math here — purely forwards buffer calls into the geodesic coordinate system.
 */
UCLASS()
class CATALYSTLANDFORM_API UCLVoxelFunctionLibrary : public UVoxelFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform", meta=(DisplayName="World → STR (buffer)"))
	static void CL_WorldToSTR(
		const FVoxelDoubleVectorBuffer& WorldPos,
		double CoreRadiusM,
		double MaxHeightM,
		FVoxelDoubleBuffer& S,
		FVoxelDoubleBuffer& T,
		FVoxelDoubleBuffer& R);

	UFUNCTION(BlueprintPure, Category="Catalyst|Landform", meta=(DisplayName="STR → World (buffer)"))
	static void CL_STRToWorld(
		const FVoxelDoubleBuffer& S,
		const FVoxelDoubleBuffer& T,
		const FVoxelDoubleBuffer& R,
		double CoreRadiusM,
		double MaxHeightM,
		FVoxelDoubleVectorBuffer& OutWorldPos);
};