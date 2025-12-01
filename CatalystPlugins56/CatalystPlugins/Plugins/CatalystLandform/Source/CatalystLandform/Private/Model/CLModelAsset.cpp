/**
 * @file CLModelAsset.cpp
 * @brief Implementation for Landform model asset. Relies on the
 *        Foundation base for JSON import/export and provenance handling.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#include "Model/CLModelAsset.h"
#include "Validation/CFValidationTypes.h"

// ---------------- Normalization ----------------

void UCLModelAsset::NormalizePayload()
{
	// Intentionally empty: normalization rules based on plugin requirements.
}

// ---------------- Validation ----------------

bool UCLModelAsset::ValidatePayload(FString& OutError) const
{
	// Keep permissive until rules are formalized.
	// Example (when needed):
	// if (Model.Value.Num() == 0)
	// {
	//     OutError = TEXT("At least one Value is required.");
	//     return false;
	// }
	return true;
}

void UCLModelAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Example structure for future plugin-level validation:
	// 	if (Model.Value.Num() == 0)
	// 	{
	// 		OutMessages.Add(FCFValidationMessage::Make(
	// 			ECFValidationSeverity::Warning,
	// 			TEXT("CL.Value.Empty"),
	// 			NSLOCTEXT("CL", "Val_NoValue", "No value defined."),
	// 			FText(), TEXT("/Landform")));
	// 	}
}
