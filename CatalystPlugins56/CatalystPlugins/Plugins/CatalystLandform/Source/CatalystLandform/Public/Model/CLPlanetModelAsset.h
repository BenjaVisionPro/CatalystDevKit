/**
 * @file CLPlanetModelAsset.h
 * @brief Landform planet model asset
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"   // Foundation base (JSON/import/export + provenance)
#include "Model/CLPlanetModel.h"
#include "CLPlanetModelAsset.generated.h"

/**
 * @brief Planet asset for Catalyst Landform. Used by VPP component & runtime.
 */
UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLPlanetModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** Full editable planet model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Model")
	FCLPlanetModel Model;

	/** Lightweight summary for editor and diagnostics. */
	virtual FString GetSummaryText() const override
	{
		return TEXT("Planet model (radius + shell thickness).");
	}

	/** Direct accessors for tools that avoid JSON round-trips. */
	const FCLPlanetModel& GetModel() const { return Model; }
	FCLPlanetModel&       GetModel()       { return Model; }

protected:
	// ---------- Foundation integration (paths + schema + payload binding) ----------
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystLandform"); }

	/** Bump this when FCLPlanetModel schema changes to surface in version metadata/UI. */
	virtual int32   GetSchemaVersion() const override { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCLPlanetModel::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	// ---------- Normalization + validation ----------
	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};