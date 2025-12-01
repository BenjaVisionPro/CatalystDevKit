/**
 * @file CLPlanetModelAsset.cpp
 * @brief Implementation for Landform planet model asset. Relies on the
 *        Foundation base for JSON import/export and provenance handling.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#include "Model/CLPlanetModelAsset.h"
#include "Validation/CFValidationTypes.h"

// ---------------- Normalization ----------------

void UCLPlanetModelAsset::NormalizePayload()
{
	// Optional: clamp to sane ranges if desired
	// Model.ClampModel();
}

// ---------------- Validation ----------------

bool UCLPlanetModelAsset::ValidatePayload(FString& OutError) const
{
	// Keep permissive until rules are formalized.
	// Example (when needed):
	// if (!Model.IsValid())
	// {
	//     OutError = TEXT("Planet model is invalid.");
	//     return false;
	// }

	return true;
}

void UCLPlanetModelAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Example structure for future plugin-level validation:
	// if (!Model.IsValid())
	// {
	//     OutMessages.Add(FCFValidationMessage::Make(
	//         ECFValidationSeverity::Warning,
	//         TEXT("CLPlanet.InvalidModel"),
	//         NSLOCTEXT("CL", "Val_InvalidPlanetModel", "Planet model is invalid."),
	//         FText(), TEXT("/Landform/Planet")));
	// }
}