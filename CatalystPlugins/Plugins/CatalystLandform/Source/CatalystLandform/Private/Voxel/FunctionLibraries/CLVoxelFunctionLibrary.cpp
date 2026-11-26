// Copyright © Catalyst

#include "Voxel/FunctionLibraries/CLVoxelFunctionLibrary.h"

#include "Kernel/CLGeodesicCoordinateSpace.h"
#include "VoxelGraphQuery.h"

namespace
{
	struct FResolvedContext
	{
		FTransform LocalToWorld = FTransform::Identity;
		FCLGeodesicConfig Geodesic{1000.0, 2000.0};
	};

	FResolvedContext ResolveContext(const FVoxelGraphQuery& Query, double InnerRadiusM, double WorldHeightM)
	{
		FResolvedContext Result;
		if (const auto* Uniforms = Query->FindParameter<FVoxelGraphParameters::FCLUniforms>())
		{
			Result.LocalToWorld = Uniforms->LocalToWorld;
			Result.Geodesic = {Uniforms->InnerRadiusM, Uniforms->WorldHeightM};
		}
		if (InnerRadiusM > 0.0 && WorldHeightM > 0.0)
		{
			Result.Geodesic = {InnerRadiusM, WorldHeightM};
		}
		return Result;
	}
}

// ============================================================================
// Float path
// ============================================================================

void UCLVoxelFunctionLibrary::Position2DToLandform2D(
	const FVoxelGraphQuery& Query,
	const FVoxelVector2DBuffer& Position2D_LocalCM,
	const double InnerRadiusM_Override,
	const double WorldHeightM_Override,
	FVoxelVector2DBuffer& Landform2D_M,
	TSharedPtr<const FVoxelFloatBuffer>& S_Opt,
	TSharedPtr<const FVoxelFloatBuffer>& T_Opt,
	TSharedPtr<const FVoxelFloatBuffer>& R_M_Opt)
{
	const auto Context = ResolveContext(Query, InnerRadiusM_Override, WorldHeightM_Override);

	const int32 Count = Position2D_LocalCM.Num();

	// Linear tangent plane in meters from local cm
	Landform2D_M.X.Allocate(Count);
	Landform2D_M.Y.Allocate(Count);
	for (int32 i = 0; i < Count; i++)
	{
		Landform2D_M.X.Set(i, Position2D_LocalCM.X[i] * 0.01f);
		Landform2D_M.Y.Set(i, Position2D_LocalCM.Y[i] * 0.01f);
	}

	// Advanced (optional) S/T/R
	const bool bNeedS = S_Opt.IsValid();
	const bool bNeedT = T_Opt.IsValid();
	const bool bNeedR = R_M_Opt.IsValid();

	if (!bNeedS && !bNeedT && !bNeedR)
	{
		S_Opt.Reset(); T_Opt.Reset(); R_M_Opt.Reset();
		return;
	}

	TSharedRef<FVoxelFloatBuffer> SRef = MakeShared<FVoxelFloatBuffer>();
	TSharedRef<FVoxelFloatBuffer> TRef = MakeShared<FVoxelFloatBuffer>();
	TSharedRef<FVoxelFloatBuffer> RRef = MakeShared<FVoxelFloatBuffer>();

	if (bNeedS) SRef->Allocate(Count);
	if (bNeedT) TRef->Allocate(Count);
	if (bNeedR) RRef->Allocate(Count);

	for (int32 i = 0; i < Count; i++)
	{
		const FVector3d Lcm(
			static_cast<double>(Position2D_LocalCM.X[i]),
			static_cast<double>(Position2D_LocalCM.Y[i]),
			0.0);

		double S, T, Rm;
		const FVector3d WorldM = Context.LocalToWorld.TransformPosition(Lcm) * 0.01;
		FCLGeodesicCoordinateSpace::WorldToSTR(WorldM, Context.Geodesic, S, T, Rm);

		if (bNeedS) SRef->Set(i, static_cast<float>(S));
		if (bNeedT) TRef->Set(i, static_cast<float>(T));
		if (bNeedR) RRef->Set(i, static_cast<float>(Rm));
	}

	if (bNeedS) S_Opt = StaticCastSharedRef<const FVoxelFloatBuffer>(SRef);
	else        S_Opt.Reset();

	if (bNeedT) T_Opt = StaticCastSharedRef<const FVoxelFloatBuffer>(TRef);
	else        T_Opt.Reset();

	if (bNeedR) R_M_Opt = StaticCastSharedRef<const FVoxelFloatBuffer>(RRef);
	else        R_M_Opt.Reset();
}

void UCLVoxelFunctionLibrary::Landform2DToPosition2D(
	const FVoxelGraphQuery& Query,
	const FVoxelVector2DBuffer& Landform2D_M,
	const FVoxelFloatBuffer* S_Opt,
	const FVoxelFloatBuffer* T_Opt,
	const FVoxelFloatBuffer* R_M_Opt,
	FVoxelVector2DBuffer& Position2D_LocalCM)
{
	VOXEL_FUNCTION_COUNTER();

	const int32 Count = Landform2D_M.Num();
	Position2D_LocalCM.X.Allocate(Count);
	Position2D_LocalCM.Y.Allocate(Count);

	// Inverse of the plane: meters -> cm
	for (int32 i = 0; i < Count; i++)
	{
		Position2D_LocalCM.X.Set(i, Landform2D_M.X[i] * 100.0f);
		Position2D_LocalCM.Y.Set(i, Landform2D_M.Y[i] * 100.0f);
	}

	// S/T/R not required for this linear inverse; pointers accepted for compatibility.
}

// ============================================================================
// Double path
// ============================================================================

void UCLVoxelFunctionLibrary::Position2DToLandform2D_Double(
	const FVoxelGraphQuery& Query,
	const FVoxelDoubleVector2DBuffer& Position2D_LocalCM,
	const double InnerRadiusM_Override,
	const double WorldHeightM_Override,
	FVoxelDoubleVector2DBuffer& Landform2D_M,
	FVoxelDoubleBuffer& SOut,
	FVoxelDoubleBuffer& TOut,
	FVoxelDoubleBuffer& R_MOut)
{
	const auto Context = ResolveContext(Query, InnerRadiusM_Override, WorldHeightM_Override);

	const int32 Count = Position2D_LocalCM.Num();

	Landform2D_M.X.Allocate(Count);
	Landform2D_M.Y.Allocate(Count);
	for (int32 i = 0; i < Count; i++)
	{
		Landform2D_M.X.Set(i, Position2D_LocalCM.X[i] * 0.01);
		Landform2D_M.Y.Set(i, Position2D_LocalCM.Y[i] * 0.01);
	}

	SOut.Allocate(Count);
	TOut.Allocate(Count);
	R_MOut.Allocate(Count);

	for (int32 i = 0; i < Count; i++)
	{
		const FVector3d Lcm(Position2D_LocalCM.X[i], Position2D_LocalCM.Y[i], 0.0);

		double S, T, Rm;
		const FVector3d WorldM = Context.LocalToWorld.TransformPosition(Lcm) * 0.01;
		FCLGeodesicCoordinateSpace::WorldToSTR(WorldM, Context.Geodesic, S, T, Rm);

		SOut.Set(i, S);
		TOut.Set(i, T);
		R_MOut.Set(i, Rm);
	}
}

void UCLVoxelFunctionLibrary::Landform2DToPosition2D_Double(
	const FVoxelGraphQuery& Query,
	const FVoxelDoubleVector2DBuffer& Landform2D_M,
	const FVoxelDoubleBuffer& S,
	const FVoxelDoubleBuffer& T,
	const FVoxelDoubleBuffer& R_M,
	FVoxelDoubleVector2DBuffer& Position2D_LocalCM)
{
	VOXEL_FUNCTION_COUNTER();

	const int32 Count = Landform2D_M.Num();
	Position2D_LocalCM.X.Allocate(Count);
	Position2D_LocalCM.Y.Allocate(Count);

	for (int32 i = 0; i < Count; i++)
	{
		Position2D_LocalCM.X.Set(i, Landform2D_M.X[i] * 100.0);
		Position2D_LocalCM.Y.Set(i, Landform2D_M.Y[i] * 100.0);
	}
}
