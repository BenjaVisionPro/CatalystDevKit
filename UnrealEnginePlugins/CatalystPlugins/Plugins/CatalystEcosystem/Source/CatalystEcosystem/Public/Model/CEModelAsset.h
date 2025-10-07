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
 *        Tools read/write through the Foundation JSON helpers and payload accessors.
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
		return FString::Printf(TEXT("Ecosystems:%d  Biomes:%d  Animals:%d  Resources:%d"),
			Model.Ecosystems.Num(), Model.Biomes.Num(), Model.Animals.Num(), Model.Resources.Num());
	}

	/** Direct accessors for tools that avoid JSON round-trips. */
	const FCEModel& GetModel() const { return Model; }
	FCEModel&       GetModel()       { return Model; }

protected:
	// ---------- Foundation integration (paths + schema + payload binding) ----------
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystEcosystem"); }
	/** Bump this when FCEModel schema changes to surface in version metadata/UI. */
	virtual int32   GetSchemaVersion() const override { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCEModel::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	// ---------- Normalization + validation ----------
	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};