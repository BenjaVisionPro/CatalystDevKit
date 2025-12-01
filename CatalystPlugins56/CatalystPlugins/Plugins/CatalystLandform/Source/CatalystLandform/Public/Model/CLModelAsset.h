/**
 * @file CLModelAsset.h
 * @brief Landform model asset: a UPrimaryDataAsset wrapper that hosts the
 *        concrete FCLModel payload and plugs into Foundation’s JSON + versioning
 *        helpers via GetPayload* overrides.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"   // Foundation base (JSON/import/export + provenance)
#include "Model/CLModel.h"
#include "CLModelAsset.generated.h"

/**
 * @brief Root asset for Catalyst Landform. Owns the full FCLModel payload.
 *        Tools read/write through the Foundation JSON helpers and payload accessors.
 */
UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** Full editable model for this plugin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Model")
	FCLModel Model;

	/** Lightweight summary for editor and diagnostics. */
	virtual FString GetSummaryText() const override
	{
		return FString::Printf(TEXT("No summary defined yet. Update CLModelAsset."));
	}

	/** Direct accessors for tools that avoid JSON round-trips. */
	const FCLModel& GetModel() const { return Model; }
	FCLModel&       GetModel()       { return Model; }

protected:
	// ---------- Foundation integration (paths + schema + payload binding) ----------
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystLandform"); }
	/** Bump this when FCLModel schema changes to surface in version metadata/UI. */
	virtual int32   GetSchemaVersion() const override { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCLModel::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	// ---------- Normalization + validation ----------
	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};