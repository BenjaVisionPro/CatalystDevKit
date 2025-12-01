// ============================================================================
// CLGeodesicCoordinateSpace
// Seam-safe planetary coordinate mapping (World <-> (S,T,R))
// ============================================================================
//
// This defines the canonical coordinate space for Catalyst:Landform.
// - Converts between Unreal world space (FVector) and normalized planetary
//   coordinates (S,T,R).
// - Handles seam wrapping, pole stabilization, and configurable radius/height.
// - Provides utilities used by both VPP graphs and C++ generators.
// - No noise or shaping — purely mathematical projection.
// ============================================================================

#pragma once
#include "CoreMinimal.h"

// Configuration for the coordinate space
struct FCLGeodesicConfig
{
	// Planetary dimensions in meters
	double CoreRadiusM   = 1000.0;  // inner bound, non-traversable
	double MaxHeightM    = 500.0;   // distance from core surface to max altitude
	double PoleEpsilon   = 1e-6;    // prevents NaNs at poles
};

// ---------------------------------------------------------------------------
// Coordinate space mapping helpers
// ---------------------------------------------------------------------------
struct FCLGeodesicCoordinateSpace
{
	/** Convert world-space position to normalized spherical coordinates (S,T,R)
	 *  S = longitude in [0,1)
	 *  T = latitude  in [0,1]
	 *  R = radial distance from the planet core in meters
	 */
	static FORCEINLINE void WorldToSTR(
		const FVector3d& WorldPos,
		const FCLGeodesicConfig& Cfg,
		double& OutS, double& OutT, double& OutR)
	{
		const double R = WorldPos.Length();
		OutR = FMath::Max(0.0, R - Cfg.CoreRadiusM);

		// Longitude: atan2(Y,X) mapped to [0,1)
		const double Lon = FMath::Atan2(WorldPos.Y, WorldPos.X);
		OutS = FMath::Fmod((Lon / (2.0 * PI) + 1.0), 1.0);

		// Latitude: Asin(Z/R)
		const double RSafe = FMath::Max(R, Cfg.PoleEpsilon);
		const double SinLat = FMath::Clamp(WorldPos.Z / RSafe, -1.0, 1.0);
		const double Lat = FMath::Asin(SinLat); // [-pi/2, pi/2]
		OutT = (Lat / PI) + 0.5;                // [0,1]
	}

	/** Convert normalized spherical coordinates back to world-space position */
	static FORCEINLINE FVector3d STRToWorld(
		double S, double T, double R,
		const FCLGeodesicConfig& Cfg)
	{
		const double Lon = (S - FMath::Floor(S)) * 2.0 * PI; // wrap
		const double Lat = (T - 0.5) * PI;
		const double Radius = Cfg.CoreRadiusM + R;

		const double CosLat = FMath::Cos(Lat);
		const double X = Radius * CosLat * FMath::Cos(Lon);
		const double Y = Radius * CosLat * FMath::Sin(Lon);
		const double Z = Radius * FMath::Sin(Lat);

		return FVector3d(X, Y, Z);
	}

	/** Ensures S is wrapped to [0,1) to maintain seam continuity */
	static FORCEINLINE double WrapS(double S)
	{
		return FMath::Fmod(S >= 0.0 ? S : (S - FMath::Floor(S)), 1.0);
	}
};