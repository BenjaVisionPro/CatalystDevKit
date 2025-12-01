// Copyright © Catalyst

#pragma once

#include "CoreMinimal.h"
#include "CLWorldGeneratorModel.h"

/**
 * Local frame sourced from the Voxel runtime config.
 * Note: positions are in cm (UE/VPP space); rotations in world space.
 */
struct CATALYSTLANDFORM_API FCLLocalFrame
{
	FVector3d CenterWS = FVector3d::ZeroVector; // in centimeters
	FQuat     RotWS    = FQuat::Identity;       // actor/world rotation (E/N/U axes)

	// Convenience: build directly from the runtime LocalToWorld transform
	explicit FCLLocalFrame(const FTransform& T)
		: CenterWS(T.GetTranslation())
		, RotWS(T.GetRotation())
	{}
	FCLLocalFrame() = default;

	// Convenience unit axes in world space
	FORCEINLINE FVector3d EastWS()  const { return RotWS.GetAxisX(); } // +X
	FORCEINLINE FVector3d NorthWS() const { return RotWS.GetAxisY(); } // +Y
	FORCEINLINE FVector3d UpWS()    const { return RotWS.GetAxisZ(); } // +Z
};

/** Pluggable coordinate strategy. Stateless, thread-safe. */
struct CATALYSTLANDFORM_API ICLCoordinateSpace
{
	virtual ~ICLCoordinateSpace() = default;

	/**
	 * Convert Local XYZ (cm, VPP LocalSpace) to:
	 *  - S,T (unitless), R_M (meters altitude),
	 *  - XY_M (meters along local tangent plane: East = X, North = Y),
	 *  - Dir3D (unit sphere direction in planet frame).
	 */
	virtual void LocalXYZToSTRMeters(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		const FVector3d& LocalXYZ_cm,
		/*out*/ double& OutS,
		/*out*/ double& OutT,
		/*out*/ double& OutR_M,
		/*out*/ FVector2d& OutXY_M,
		/*out*/ FVector3d& OutDir3D
	) const = 0;

	/** Convert (S,T,R_M) back to **World** position (cm). */
	virtual FVector3d STRToWorld_cm(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		double S, double T, double R_M
	) const = 0;

	/** Convert **World** position (cm) to (S,T,R_M). */
	virtual void WorldToSTR(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		const FVector3d& World_cm,
		/*out*/ double& OutS,
		/*out*/ double& OutT,
		/*out*/ double& OutR_M
	) const = 0;
};

/** Registry to resolve the active coordinate strategy. */
struct CATALYSTLANDFORM_API FCLCoordSpaceRegistry
{
	static const ICLCoordinateSpace& Resolve(ECLCoordSpace Space);
};