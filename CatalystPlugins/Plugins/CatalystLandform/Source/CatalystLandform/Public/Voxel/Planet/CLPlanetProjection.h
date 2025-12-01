// Catalyst Landform - Planet projection placeholders
#pragma once

#include "VoxelMinimal.h"
#include "CLPlanetProjection.generated.h"

UENUM(BlueprintType)
enum class ECLPlanetProjection : uint8
{
	TangentPlane UMETA(DisplayName="Tangent Plane (ENU)"),
	Gnomonic     UMETA(DisplayName="Gnomonic"),
	CubedSphere  UMETA(DisplayName="Cubed Sphere")
};
