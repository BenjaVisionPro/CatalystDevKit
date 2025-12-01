#include "Model/CLStrataAsset.h"
#include "Validation/CFValidationTypes.h"

void UCLStrataAsset::NormalizePayload()
{
	// Nothing to do yet
}

bool UCLStrataAsset::ValidatePayload(FString& OutError) const
{
	return Strata.IsValid();
}

void UCLStrataAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Optional warnings could go here
}