/**
 * @file __PREFIX__ModelAsset.h
 * @brief __PLUGIN_DISPLAY_NAME__ model asset: a UPrimaryDataAsset wrapper that hosts the
 *        concrete F__PREFIX__Model payload and plugs into Foundation’s JSON + versioning
 *        helpers via GetPayload* overrides.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"   // Foundation base (JSON/import/export + provenance)
#include "Model/__PREFIX__Model.h"
#include "__PREFIX__ModelAsset.generated.h"

/**
 * @brief Root asset for Catalyst __PLUGIN_DISPLAY_NAME__. Owns the full F__PREFIX__Model payload.
 *        Tools read/write through the Foundation JSON helpers and payload accessors.
 */
UCLASS(BlueprintType)
class __PLUGIN_API__ U__PREFIX__ModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** Full editable model for this plugin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="__PLUGIN_DISPLAY_NAME__|Model")
	F__PREFIX__Model Model;

	/** Lightweight summary for editor and diagnostics. */
	virtual FString GetSummaryText() const override
	{
		return FString::Printf(TEXT("No summary defined yet. Update __PREFIX__ModelAsset."));
	}

	/** Direct accessors for tools that avoid JSON round-trips. */
	const F__PREFIX__Model& GetModel() const { return Model; }
	F__PREFIX__Model&       GetModel()       { return Model; }

protected:
	// ---------- Foundation integration (paths + schema + payload binding) ----------
	virtual FString GetPluginNameForPaths() const override { return TEXT("__PLUGIN_NAME__"); }
	/** Bump this when F__PREFIX__Model schema changes to surface in version metadata/UI. */
	virtual int32   GetSchemaVersion() const override { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return F__PREFIX__Model::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	// ---------- Normalization + validation ----------
	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};