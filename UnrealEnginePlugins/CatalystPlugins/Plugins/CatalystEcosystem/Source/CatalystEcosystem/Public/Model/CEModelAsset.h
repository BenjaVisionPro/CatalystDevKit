/**
 * @file CEModelAsset.h
 * @brief Ecosystems model asset: a UPrimaryDataAsset wrapper that hosts the
 *        concrete FCEModel payload and plugs into Foundation’s JSON + versioning
 *        helpers via GetPayload* overrides.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"   // Foundation base (JSON/import/export + provenance)
#include "Model/CEModel.h"
#include "CEModelAsset.generated.h"

/**
 * @brief Root asset for Catalyst Ecosystem. Owns the full FCEModel payload.
 *        No extra surface beyond the Foundation base; tools read/write through
 *        the standard JSON helpers and the GetPayload* accessors below.
 */
UCLASS(BlueprintType)
class CATALYSTECOSYSTEM_API UCEModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** Full editable model for this plugin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CE|Model")
	FCEModel Model;

	/** Lightweight summary for editor and diagnostics. */
	virtual FString GetSummaryText() const override
	{
		// Keep this stable and cheap: counts only.
		return FString::Printf(TEXT("Ecosystems:%d  Biomes:%d  Animals:%d  Resources:%d"),
			Model.Ecosystems.Num(), Model.Biomes.Num(), Model.Animals.Num(), Model.Resources.Num());
	}

	/** Direct accessors for tools that avoid JSON round-trips. */
	const FCEModel& GetModel() const { return Model; }
	FCEModel&       GetModel()       { return Model; }

protected:
	// ---------- Foundation integration (payload + paths) ----------

	/** Saved/<Plugin>/Model.json lives under this folder name. */
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystEcosystem"); }

	/** Map the Foundation JSON helpers to our concrete payload. */
	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCEModel::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	// ---------- Validation seam (opt-in; keep lean) ----------

	/**
	 * @brief Deterministically normalize payload (no-op by default).
	 *        Add clamping/sorting/default fill here when rules are defined.
	 */
	virtual void NormalizePayload() override
	{
		// Intentionally empty: we haven’t defined normalization rules yet.
		// Example (when needed):
		// Model.Biomes.Sort([](const FBio& A, const FBio& B){ return A.Id < B.Id; });
	}

	/**
	 * @brief Validate invariants (no-op pass for now).
	 *        Return false with a precise error message to block save/export.
	 */
	virtual bool ValidatePayload(FString& OutError) const override
	{
		// Keep permissive until rules are formalised.
		// Example (when needed):
		// if (Model.Ecosystems.Num() == 0) { OutError = TEXT("At least one Ecosystem is required."); return false; }
		return true;
	}
};