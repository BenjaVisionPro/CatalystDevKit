#pragma once

#include "CoreMinimal.h"
#include "Model/CLStrata.h"

// One vertical "column": discrete height -> shared immutable sample set
struct CATALYSTLANDFORM_API FCLStrataCache
{
	// Mutable lets const GetOrBuild populate cache safely
	mutable TMap<int32, TSharedPtr<const TArray<FCLStratumSample>>> ByHeight;

	static FORCEINLINE int32 QuantizeHeight(const double AltitudeN, const int32 Resolution)
	{
		const double X = FMath::Clamp(AltitudeN, 0.0, 1.0);
		return FMath::Clamp(FMath::RoundToInt(X * Resolution), 0, Resolution);
	}

	FORCEINLINE void Invalidate()
	{
		ByHeight.Reset();
	}

	TSharedPtr<const TArray<FCLStratumSample>> GetOrBuild(
		const FCLStrata& Strata,
		const int32 HeightIndex,
		const bool bNormalize,
		const int32 Resolution) const
	{
		if (const auto* Found = ByHeight.Find(HeightIndex))
		{
			return *Found;
		}

		TArray<FCLStratumSample> Built;
		const double AltN = (Resolution > 0) ? double(HeightIndex) / double(Resolution) : 0.0;
		Strata.Sample(AltN, bNormalize, Built);

		TSharedPtr<TArray<FCLStratumSample>> Owned = MakeShared<TArray<FCLStratumSample>>(MoveTemp(Built));
		TSharedPtr<const TArray<FCLStratumSample>>& Slot = ByHeight.FindOrAdd(HeightIndex);
		if (!Slot.IsValid())
		{
			Slot = StaticCastSharedPtr<const TArray<FCLStratumSample>>(Owned);
		}
		return Slot;
	}
};