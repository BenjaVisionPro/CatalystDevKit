#include "Model/CLStrataAsset.h"
#include "Validation/CFValidationTypes.h"

TSharedPtr<const TArray<FCLStratumSample>> UCLStrataAsset::SampleStrataShared_Resolution(
	const int32 Resolution, const int32 HeightIndex, const bool bNormalize) const
{
	Cache.EnsureResolution(Resolution);
	return Cache.GetOrBuild(Strata, HeightIndex, bNormalize);
}

void UCLStrataAsset::NormalizePayload()
{
	Cache.Invalidate();
}

bool UCLStrataAsset::ValidatePayload(FString& OutError) const
{
	return Strata.IsValid();
}

void UCLStrataAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Optional non-fatal warnings can go here.
}