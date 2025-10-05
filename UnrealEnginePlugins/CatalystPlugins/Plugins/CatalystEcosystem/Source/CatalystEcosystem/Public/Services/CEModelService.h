// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h"

// We include full types because we expose typed accessors here.
#include "Model/CEModelAsset.h"
#include "CEModelService.generated.h"

/**
 * Ecosystem Model Service
 *
 * - Uniform with other plugins: inherits UCFAbstractModelService.
 * - Provides compile-time plugin identity and seed asset location.
 * - Exposes simple, typed getters for the CE asset and the CEModel struct.
 * - Adds a small static Instance() for convenience in editor/UI code.
 */
UCLASS()
class CATALYSTECOSYSTEM_API UCEModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// ---------- Identity & seed (compile-time enforced by override) ----------
	virtual FName GetPluginName() const override { return TEXT("CatalystEcosystem"); }

	/** Where the seed asset lives (produced by the commandlet from /Model/<modelName>.json). */
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		// Must match the package name written by CFGenerateModelAssetsCommandlet.
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/CatalystEcosystem/Model/CEModelAsset_Seed.CEModelAsset_Seed")));
	}

	// ---------- Convenience access ----------
	/** Fast path to the service (works in PIE/Editor via foundation’s Find<T> helper). */
	static UCEModelService* Instance() { return UCFAbstractModelService::Find<UCEModelService>(); }

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
