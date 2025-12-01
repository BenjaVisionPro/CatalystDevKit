// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h"   // Foundation base
#include "Model/CLModelAsset.h"                // typed accessors
#include "CLModelService.generated.h"

/**
 * Ecosystem Model Service
 *
 * - Inherits UCFAbstractModelService (Foundation).
 * - Provides compile-time plugin identity and seed asset location.
 * - Exposes typed getters for the CE asset and CLModel struct.
 */
UCLASS()
class CATALYSTLANDFORM_API UCLModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// ---------- Identity & seed ----------
	virtual FName GetPluginName() const override { return TEXT("CatalystLandform"); }

	/** Where the seed asset lives (produced by the commandlet from /Model/<modelName>.json). */
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		// Must match the package name written by CFGenerateModelAssetsCommandlet.
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/CatalystLandform/Model/CLModelAsset_Seed.CLModelAsset_Seed")));
	}

	// ---------- Convenience access ----------
	/** Best-effort singleton-style accessor (editor/runtime). May return nullptr. */
	static UCLModelService* Instance();

	/** Live CE model asset (read-only). May be null early in init. */
	const UCLModelAsset* GetModelAsset() const { return Cast<UCLModelAsset>(Get()); }

	/** Live CE model asset (mutable). */
	UCLModelAsset* GetMutableModelAsset() { return Cast<UCLModelAsset>(GetMutable()); }

	/** Root CLModel struct pointer (read-only). */
	const FCLModel* GetModel() const
	{
		if (const UCLModelAsset* A = GetModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}

	/** Root CLModel struct pointer (mutable). */
	FCLModel* GetMutableModel()
	{
		if (UCLModelAsset* A = GetMutableModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}
};