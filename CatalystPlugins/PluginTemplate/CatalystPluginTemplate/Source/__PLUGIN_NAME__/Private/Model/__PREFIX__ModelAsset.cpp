/**
 * @file __PREFIX__ModelAsset.cpp
 * @brief Implementation for __PLUGIN_DISPLAY_NAME__ model asset. Relies on the
 *        Foundation base for JSON import/export and provenance handling.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#include "Model/__PREFIX__ModelAsset.h"
#include "Validation/CFValidationTypes.h"

// ---------------- Normalization ----------------

void U__PREFIX__ModelAsset::NormalizePayload()
{
	// Intentionally empty: normalization rules based on plugin requirements.
}

// ---------------- Validation ----------------

bool U__PREFIX__ModelAsset::ValidatePayload(FString& OutError) const
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

void U__PREFIX__ModelAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Example structure for future plugin-level validation:
	// 	if (Model.Value.Num() == 0)
	// 	{
	// 		OutMessages.Add(FCFValidationMessage::Make(
	// 			ECFValidationSeverity::Warning,
	// 			TEXT("__PREFIX__.Value.Empty"),
	// 			NSLOCTEXT("__PREFIX__", "Val_NoValue", "No value defined."),
	// 			FText(), TEXT("/__PLUGIN_DISPLAY_NAME__")));
	// 	}
}
