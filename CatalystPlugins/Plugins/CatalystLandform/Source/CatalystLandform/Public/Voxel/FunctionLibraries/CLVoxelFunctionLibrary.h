// Copyright © Catalyst
#pragma once

#include "CoreMinimal.h"
#include "VoxelFunctionLibrary.h"
#include "Buffer/VoxelFloatBuffers.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "CLVoxelFunctionLibrary.generated.h"

// Forward decls
struct FCLWorldGeneratorModel;
struct FCLLocalFrame;
struct ICLCoordinateSpace;

/**
 * Graph uniforms available on FVoxelGraphQuery (VPP 2.0p8 pattern).
 * Stored on the query via Query->FindParameter<FVoxelGraphParameters::FCLUniforms>().
 */
namespace FVoxelGraphParameters
{
	struct CATALYSTLANDFORM_API FCLUniforms : FUniformParameter
	{
		FTransform LocalToWorld = FTransform::Identity;

		double InnerRadiusM   = 1000.0;
		double WorldHeightM   = 2000.0;

		int32  CoordSpaceInt  = 0;     // cast to ECLCoordSpace
		double SeamBlendWidth = 0.001;

		uint32 Seed           = 0;
	};
}

/**
 * Central Landform coordinate helpers.
 * Static C++ methods used by compute nodes (not exposed as graph nodes).
 * All methods are pure, pass Query explicitly, and delegate math to the pluggable ICLCoordinateSpace.
 */
UCLASS()
class CATALYSTLANDFORM_API UCLVoxelFunctionLibrary : public UVoxelFunctionLibrary
{
	GENERATED_BODY()

public:
	// ------------------------------------------------------------------------
	// 2D (Float path): GetPosition2D (Float cm)  <->  Landform2D (meters)
	// ------------------------------------------------------------------------

	/**
	 * Local 2D (cm, Z=0) -> linear Landform2D (meters tangent-plane XY).
	 * Optionally returns S/T/R (float) if the TSharedPtr outputs are already valid.
	 * If the caller passes null shared pointers, S/T/R are skipped.
	 */
	static void Position2DToLandform2D(
		const FVoxelGraphQuery& Query,
		const FVoxelVector2DBuffer& Position2D_LocalCM,
		double InnerRadiusM_Override,
		double WorldHeightM_Override,
		/*out*/ FVoxelVector2DBuffer& Landform2D_M,
		/*inout opt*/ TSharedPtr<const FVoxelFloatBuffer>& S_Opt,
		/*inout opt*/ TSharedPtr<const FVoxelFloatBuffer>& T_Opt,
		/*inout opt*/ TSharedPtr<const FVoxelFloatBuffer>& R_M_Opt);

	/**
	 * Landform2D (meters XY) (+ optional S/T/R) -> Local 2D (cm).
	 * For the current linear Landform2D mapping this is just meters->cm.
	 */
	static void Landform2DToPosition2D(
		const FVoxelGraphQuery& Query,
		const FVoxelVector2DBuffer& Landform2D_M,
		const FVoxelFloatBuffer* S_Opt,
		const FVoxelFloatBuffer* T_Opt,
		const FVoxelFloatBuffer* R_M_Opt,
		/*out*/ FVoxelVector2DBuffer& Position2D_LocalCM);

	// ------------------------------------------------------------------------
	// 2D (Double path): GetPosition2D (Double cm)  <->  Landform2D (meters)
	// ------------------------------------------------------------------------

	/** Local 2D (cm, Z=0) -> STR (m) & Landform2D (meters tangent-plane XY, double precision) */
	static void Position2DToLandform2D_Double(
		const FVoxelGraphQuery& Query,
		const FVoxelDoubleVector2DBuffer& Position2D_LocalCM,
		double InnerRadiusM_Override,
		double WorldHeightM_Override,
		/*out*/ FVoxelDoubleVector2DBuffer& Landform2D_M,
		/*out*/ FVoxelDoubleBuffer& S,
		/*out*/ FVoxelDoubleBuffer& T,
		/*out*/ FVoxelDoubleBuffer& R_M);

	/** Landform2D (meters XY, double) + STR (m) -> Local 2D (cm) */
	static void Landform2DToPosition2D_Double(
		const FVoxelGraphQuery& Query,
		const FVoxelDoubleVector2DBuffer& Landform2D_M,
		const FVoxelDoubleBuffer& S,
		const FVoxelDoubleBuffer& T,
		const FVoxelDoubleBuffer& R_M,
		/*out*/ FVoxelDoubleVector2DBuffer& Position2D_LocalCM);

	// ------------------------------------------------------------------------
	// 3D (Float path): GetPosition3D (Float cm)  <->  Landform3D (planet-frame meters)
	// (Restored exactly so existing nodes link.)
	// ------------------------------------------------------------------------

	/** Local 3D (cm) -> STR (m) & Landform3D (meters in planet frame) */
	static void Position3DToLandform3D(
		const FVoxelGraphQuery& Query,
		const FVoxelVectorBuffer& Position3D_LocalCM,
		double InnerRadiusM_Override,
		double WorldHeightM_Override,
		/*out*/ FVoxelVectorBuffer& Landform3D_M,
		/*out*/ FVoxelDoubleBuffer& S,
		/*out*/ FVoxelDoubleBuffer& T,
		/*out*/ FVoxelDoubleBuffer& R_M);

	/** Landform3D (meters, planet frame) + STR (m) -> Local 3D (cm) */
	static void Landform3DToPosition3D(
		const FVoxelGraphQuery& Query,
		const FVoxelVectorBuffer& Landform3D_M,
		const FVoxelDoubleBuffer& S,
		const FVoxelDoubleBuffer& T,
		const FVoxelDoubleBuffer& R_M,
		/*out*/ FVoxelVectorBuffer& Position3D_LocalCM);
};