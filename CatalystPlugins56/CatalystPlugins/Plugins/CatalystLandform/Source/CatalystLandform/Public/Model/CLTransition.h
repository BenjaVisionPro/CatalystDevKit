// ============================================================================
// CLTransition.h
// ============================================================================
#pragma once

#include "CoreMinimal.h"
#include "CLTransition.generated.h"

UENUM(BlueprintType)
enum class ECLTransitionType : uint8
{
	Linear      UMETA(DisplayName="Linear"),
	Smoothstep  UMETA(DisplayName="Smoothstep")
};

namespace CLTransition
{
	FORCEINLINE double Eval01(const ECLTransitionType Type, double T)
	{
		T = FMath::Clamp(T, 0.0, 1.0);
		switch (Type)
		{
		default:
		case ECLTransitionType::Linear:
			return T;

		case ECLTransitionType::Smoothstep:
			// 3t^2 - 2t^3, C1 continuous with zero slope at the ends
			return T * T * (3.0 - 2.0 * T);
		}
	}
}