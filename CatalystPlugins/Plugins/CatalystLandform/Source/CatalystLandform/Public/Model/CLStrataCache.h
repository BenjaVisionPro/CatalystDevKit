#pragma once

#include "CoreMinimal.h"
#include "Model/CLStrata.h"

struct CATALYSTLANDFORM_API FCLStrataCache
{
	struct FKey
	{
		int32 HeightIndex = 0;
		bool  bNormalize  = false;

		friend bool operator==(const FKey& A, const FKey& B)
		{
			return A.HeightIndex == B.HeightIndex
				&& A.bNormalize  == B.bNormalize;
		}
	};
	friend FORCEINLINE uint32 GetTypeHash(const FCLStrataCache::FKey& K)
	{
		return HashCombine(::GetTypeHash(K.HeightIndex), ::GetTypeHash(K.bNormalize));
	}

	// Sole purpose: detect change and invalidate.
	int32 Resolution = 0;

	// (HeightIndex, bNormalize) -> shared immutable array of samples
	TMap<FKey, TSharedPtr<const TArray<FCLStratumSample>>> ByHeight;

	static FORCEINLINE int32 QuantizeHeight(const double AltitudeN, const int32 InResolution)
	{
		check(InResolution > 0);
		const double X = FMath::Clamp(AltitudeN, 0.0, 1.0);
		return FMath::Clamp(static_cast<int32>(FMath::RoundHalfFromZero(X * InResolution)), 0, InResolution);
	}

	FORCEINLINE void Invalidate()
	{
		ByHeight.Reset();
		Resolution = 0;
	}

	FORCEINLINE void EnsureResolution(const int32 NewResolution)
	{
		check(NewResolution > 0);
		if (Resolution != NewResolution)
		{
			Invalidate();
			Resolution = NewResolution;
		}
	}

	TSharedPtr<const TArray<FCLStratumSample>> GetOrBuild(
		const FCLStrata& Strata,
		const int32 HeightIndex,
		const bool bNormalize)
	{
		check(Resolution > 0);
		const FKey Key{ HeightIndex, bNormalize };
		if (const TSharedPtr<const TArray<FCLStratumSample>>* Found = ByHeight.Find(Key))
		{
			return *Found;
		}

		TArray<FCLStratumSample> Built;
		const double AltN = double(HeightIndex) / double(Resolution);
		Strata.Sample(AltN, bNormalize, Built);

		TSharedPtr<TArray<FCLStratumSample>> Owned = MakeShared<TArray<FCLStratumSample>>(MoveTemp(Built));
		TSharedPtr<const TArray<FCLStratumSample>>& Slot = ByHeight.FindOrAdd(Key);
		if (!Slot.IsValid())
		{
			Slot = StaticCastSharedPtr<const TArray<FCLStratumSample>>(Owned);
		}
		return Slot;
	}
};