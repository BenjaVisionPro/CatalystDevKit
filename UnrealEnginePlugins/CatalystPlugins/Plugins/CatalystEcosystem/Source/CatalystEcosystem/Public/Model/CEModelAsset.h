// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"   // Foundation: base asset class (formerly ModelRoot)
#include "Model/CEModel.h"
#include "CEModelAsset.generated.h"

/**
 * UCEModelAsset
 *
 * PrimaryDataAsset wrapper holding the entire Ecosystem model (FCEModel).
 * - Matches the Foundation JSON helpers by exposing GetPayload* for the 'Model' field.
 * - Provides a concise summary string for editor/diagnostics.
 */
UCLASS(BlueprintType)
class CATALYSTECOSYSTEM_API UCEModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** The full editable model for this plugin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Model")
	FCEModel Model;

	/** Accessor used by tools/UI. */
	const FCEModel& GetModel() const { return Model; }
	FCEModel&       GetModel()       { return Model; }

protected:
	// Foundation expects these exact virtuals for JSON load/save.
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystEcosystem"); }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCEModel::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Model; }
	virtual const void*    GetPayloadMemory()       const override { return &Model; }

	virtual FString GetSummaryText() const override
	{
		return FString::Printf(TEXT("Ecosystems:%d  Biomes:%d  Animals:%d  Resources:%d"),
			Model.Ecosystems.Num(), Model.Biomes.Num(), Model.Animals.Num(), Model.Resources.Num());
	}
};