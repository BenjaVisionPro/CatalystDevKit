// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h"

// We need full types here because we access GetModel() below.
#include "Model/CEModelAsset.h"
#include "CEModelService.generated.h"

/**
 * Ecosystem Model Service
 *
 * - Uniform with other plugins: inherits UCFAbstractModelService.
 * - Provides compile-time identity and seed asset path.
 * - Adds typed convenience accessors for CE.
 */
UCLASS()
class CATALYSTECOSYSTEM_API UCEModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// Compile-time plugin identity
	virtual FName GetPluginName() const override { return TEXT("CatalystEcosystem"); }

	// Where the seed asset is expected to live (generated from JSON by our importer)
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		// Path must match the package name written by the importer.
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/CatalystEcosystem/Model/CEModelAsset_Seed.CEModelAsset_Seed")));
	}

	// ---- Typed helpers (no static templates, no globals) ----

	// Return the live CE model asset (read-only)
	const UCEModelAsset* GetModelAsset() const { return Cast<UCEModelAsset>(Get()); }

	// Return the live CE model asset (mutable)
	UCEModelAsset* GetMutableModelAsset()       { return Cast<UCEModelAsset>(GetMutable()); }

	// Return the CEModel UStruct pointer (read-only). May be null before initialization.
	const FCEModel* GetModel() const
	{
		if (const UCEModelAsset* A = GetModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}

	// Return the CEModel UStruct pointer (mutable). May be null before initialization.
	FCEModel* GetMutableModel()
	{
		if (UCEModelAsset* A = GetMutableModelAsset())
		{
			return &A->GetModel();
		}
		return nullptr;
	}
};