// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h"   // Foundation base
#include "Model/__PREFIX__ModelAsset.h"                // typed accessors
#include "__PREFIX__ModelService.generated.h"

/**
 * Ecosystem Model Service
 *
 * - Inherits UCFAbstractModelService (Foundation).
 * - Provides compile-time plugin identity and seed asset location.
 * - Exposes typed getters for the CE asset and __PREFIX__Model struct.
 */
UCLASS()
class CATALYSTECOSYSTEM_API U__PREFIX__ModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// ---------- Identity & seed ----------
	virtual FName GetPluginName() const override { return TEXT("__PLUGIN_NAME__"); }

	/** Where the seed asset lives (produced by the commandlet from /Model/<modelName>.json). */
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		// Must match the package name written by CFGenerateModelAssetsCommandlet.
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/__PLUGIN_NAME__/Model/__PREFIX__ModelAsset_Seed.__PREFIX__ModelAsset_Seed")));
	}

	// ---------- Convenience access ----------
	/** Best-effort singleton-style accessor (editor/runtime). May return nullptr. */
	static U__PREFIX__ModelService* Instance();

	/** Live CE model asset (read-only). May be null early in init. */
	const U__PREFIX__ModelAsset* GetModelAsset() const { return Cast<U__PREFIX__ModelAsset>(Get()); }

	/** Live CE model asset (mutable). */
	U__PREFIX__ModelAsset* GetMutableModelAsset() { return Cast<U__PREFIX__ModelAsset>(GetMutable()); }

	/** Root __PREFIX__Model struct pointer (read-only). */
	const F__PREFIX__Model* GetModel() const
	{
		if (const U__PREFIX__ModelAsset* A = GetModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}

	/** Root __PREFIX__Model struct pointer (mutable). */
	F__PREFIX__Model* GetMutableModel()
	{
		if (U__PREFIX__ModelAsset* A = GetMutableModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}
};