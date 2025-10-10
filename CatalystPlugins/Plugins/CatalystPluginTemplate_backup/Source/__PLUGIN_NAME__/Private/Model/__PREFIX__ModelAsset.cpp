/**
 * @file __PREFIX__ModelAsset.cpp
 * @brief Implementation for the Ecosystems model asset. Relies on the
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
	// Intentionally empty: normalization rules TBD.
	// Example:
	// Model.Biomes.Sort([](const F__PREFIX__Biome& A, const F__PREFIX__Biome& B){ return A.Id < B.Id; });
}

// ---------------- Validation ----------------

bool U__PREFIX__ModelAsset::ValidatePayload(FString& OutError) const
{
	// Keep permissive until rules are formalized.
	// Example (when needed):
	// if (Model.Ecosystems.Num() == 0)
	// {
	//     OutError = TEXT("At least one Ecosystem is required.");
	//     return false;
	// }
	return true;
}

void U__PREFIX__ModelAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Example structure for future plugin-level validation:
	if (Model.Ecosystems.Num() == 0)
	{
		OutMessages.Add(FCFValidationMessage::Make(
			ECFValidationSeverity::Warning,
			TEXT("__PREFIX__.Ecosystem.Empty"),
			NSLOCTEXT("CE", "Val_NoEcosystems", "No ecosystems defined."),
			FText(), TEXT("/Ecosystems")));
	}

	for (int32 i = 0; i < Model.Biomes.Num(); ++i)
	{
		const auto& Biome = Model.Biomes[i];
		if (Biome.Title.IsEmpty())
		{
			OutMessages.Add(FCFValidationMessage::Make(
				ECFValidationSeverity::Error,
				TEXT("__PREFIX__.Biome.MissingName"),
				NSLOCTEXT("CE", "Val_BiomeMissingName", "Biome is missing a title."),
				FText(), FString::Printf(TEXT("/Biomes[%d]"), i),
				NSLOCTEXT("CE", "Val_BiomeMissingNameFix", "Enter a non-empty title.")));
		}
	}
}
