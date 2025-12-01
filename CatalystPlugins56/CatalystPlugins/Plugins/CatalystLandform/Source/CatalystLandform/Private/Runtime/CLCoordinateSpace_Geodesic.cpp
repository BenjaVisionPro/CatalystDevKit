// Copyright © Catalyst

#include "Runtime/CLCoordinateSpace.h"
#include "Runtime/CLWorldGeneratorModel.h"
#include "Kernel/CLGeodesicCoordinateSpace.h"

// Small helper for geodesic math
static FORCEINLINE FCLGeodesicConfig MakeCfg(const FCLWorldGeneratorModel& Model)
{
	FCLGeodesicConfig Cfg;
	Cfg.CoreRadiusM = Model.InnerRadiusM;
	Cfg.MaxHeightM  = Model.WorldHeightM;
	Cfg.PoleEpsilon = 1e-6;
	return Cfg;
}

// Convert World(cm) -> Planet-frame (meters)
static FORCEINLINE FVector3d WorldCm_To_PlanetM(const FCLLocalFrame& Frame, const FVector3d& World_cm)
{
	const FVector3d Delta_cm = World_cm - Frame.CenterWS;
	const FVector3d Delta_m  = Delta_cm / 100.0;
	return Frame.RotWS.Inverse().RotateVector(Delta_m);
}

// Convert Planet-frame (meters) -> World(cm)
static FORCEINLINE FVector3d PlanetM_To_WorldCm(const FCLLocalFrame& Frame, const FVector3d& Planet_m)
{
	const FVector3d World_m = Frame.RotWS.RotateVector(Planet_m);
	return World_m * 100.0 + Frame.CenterWS;
}

// Concrete geodesic strategy
struct FGeodesicSpace final : ICLCoordinateSpace
{
	// Local (VPP) cm -> STR (meters domain) + helpers
	virtual void LocalXYZToSTRMeters(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		const FVector3d& LocalXYZ_cm,
		/*out*/ double& OutS,
		/*out*/ double& OutT,
		/*out*/ double& OutR_M,
		/*out*/ FVector2d& OutXY_M,
		/*out*/ FVector3d& OutDir3D
	) const override
	{
		// Interpret LocalXYZ as local to the voxel world; lift to world using the frame.
		// (If you later need a distinct Local->World transform, carry it in FCLUniforms.)
		const FVector3d World_cm = Frame.CenterWS + Frame.RotWS.RotateVector(LocalXYZ_cm);

		// World->planet meters
		const FVector3d Planet_m = WorldCm_To_PlanetM(Frame, World_cm);

		// Geodesic STR
		const FCLGeodesicConfig Cfg = MakeCfg(Model);
		double S, T, Rm;
		FCLGeodesicCoordinateSpace::WorldToSTR(Planet_m, Cfg, S, T, Rm);

		OutS    = S;
		OutT    = T;
		OutR_M  = Rm;

		// Direction in planet frame (unit radial)
		const double Radius = (Model.InnerRadiusM + Rm);
		OutDir3D = Radius > 0.0 ? Planet_m / Radius : FVector3d::UpVector;

		// Tangent XY in meters (simple, metric-preserving local chart):
		// X = East arc length, Y = North arc length
		const double Lon = FMath::Frac(S) * 2.0 * PI;
		const double Lat = (T - 0.5) * PI;
		const double CosLat = FMath::Cos(Lat);
		const double R = Radius;

		// Approx local metric (valid for small patches):
		// ds_east  ≈ R * cos(lat) * dLon
		// ds_north ≈ R * dLat
		OutXY_M.X = R * CosLat * Lon;
		OutXY_M.Y = R * Lat;
	}

	// STR (meters) -> World(cm)
	virtual FVector3d STRToWorld_cm(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		double S, double T, double R_M
	) const override
	{
		const FCLGeodesicConfig Cfg = MakeCfg(Model);
		const FVector3d Planet_m = FCLGeodesicCoordinateSpace::STRToWorld(S, T, R_M, Cfg);
		return PlanetM_To_WorldCm(Frame, Planet_m);
	}

	// World(cm) -> STR (meters)
	virtual void WorldToSTR(
		const FCLWorldGeneratorModel& Model,
		const FCLLocalFrame& Frame,
		const FVector3d& World_cm,
		/*out*/ double& OutS,
		/*out*/ double& OutT,
		/*out*/ double& OutR_M
	) const override
	{
		const FVector3d Planet_m = WorldCm_To_PlanetM(Frame, World_cm);
		const FCLGeodesicConfig Cfg = MakeCfg(Model);
		FCLGeodesicCoordinateSpace::WorldToSTR(Planet_m, Cfg, OutS, OutT, OutR_M);
	}
};

// Singleton accessor used by the registry (keeps the type private to this TU)
const ICLCoordinateSpace& CL_GetGeodesicCoordSpace()
{
	static const FGeodesicSpace GInstance;
	return GInstance;
}