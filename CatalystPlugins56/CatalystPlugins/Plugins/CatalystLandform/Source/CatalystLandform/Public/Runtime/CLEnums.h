#pragma once

#include "CoreMinimal.h"
#include "CLEnums.generated.h"

UENUM(BlueprintType)
enum class ECLCoordSpace : uint8
{
	Geodesic UMETA(DisplayName="Geodesic"),
	// Future: CubeFace, IcosaFace, OblateSpheroid, ...
};