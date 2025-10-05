// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h"   // Foundation base
#include "Model/CEModelAsset.h"                // typed accessors
#include "CEModelService.generated.h"

/**
 * Ecosystem Model Service
 *
 * - Inherits UCFAbstractModelService (Foundation).
 * - Provides compile-time plugin identity and seed asset location.
 * - Exposes typed getters for the CE asset and CEModel struct.
 */
UCLASS()
class CATALYSTECOSYSTEM_API UCEModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// ---------- Identity & seed ----------
	virtual FName GetPluginName() const override { return TEXT("CatalystEcosystem"); }

	/** Where the seed asset lives (produced by the commandlet from /Model/<modelName>.json). */
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		// Must match the package name written by CFGenerateModelAssetsCommandlet.
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/CatalystEcosystem/Model/CEModelAsset_Seed.CEModelAsset_Seed")));
	}

	// ---------- Convenience access ----------
	/** Best-effort singleton-style accessor (editor/runtime). May return nullptr. */
	static UCEModelService* Instance();

	/** Live CE model asset (read-only). May be null early in init. */
	const UCEModelAsset* GetModelAsset() const { return Cast<UCEModelAsset>(Get()); }

	/** Live CE model asset (mutable). */
	UCEModelAsset* GetMutableModelAsset() { return Cast<UCEModelAsset>(GetMutable()); }

	/** Root CEModel struct pointer (read-only). */
	const FCEModel* GetModel() const
	{
		if (const UCEModelAsset* A = GetModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}

	/** Root CEModel struct pointer (mutable). */
	FCEModel* GetMutableModel()
	{
		if (UCEModelAsset* A = GetMutableModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}
};