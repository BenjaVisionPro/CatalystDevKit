// ============================================
// CE: GameInstance subsystem providing the live model
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Services/CFAbstractModelService.h" // from Foundation
#include "Model/CEModel.h"        // for FCEModel
#include "Model/CEModelAsset.h"   // for UCEModelAsset::GetModel()
#include "CEModelService.generated.h"

class UCEModelAsset;

/**
 * UCEModelService
 * ---------------
 * “One live model per plugin” access point for CatalystEcosystem.
 * - On Init: duplicates the seed asset and overlays Saved/CatalystEcosystem/Model.json (if present).
 * - Exposes typed helpers: GetModelAssetTyped() and GetModel().
 */
UCLASS()
class CATALYSTECOSYSTEM_API UCEModelService : public UCFAbstractModelService
{
	GENERATED_BODY()

public:
	// Identity + seed are hard-coded per plugin (compile-time enforced).
	virtual FName GetPluginName() const override { return TEXT("CatalystEcosystem"); }

	// NOTE: Update this path to match your actual seed asset location/name.
	// Example assumes you’ll create an asset:
	// /CatalystEcosystem/Model/Dev/CEModelAsset_Seed.CEModelAsset_Seed
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const override
	{
		return TSoftObjectPtr<UCFModelAsset>(
			FSoftObjectPath(TEXT("/CatalystEcosystem/Model/Dev/CEModelAsset_Seed.CEModelAsset_Seed")));
	}

	// Typed helpers for convenience
	const UCEModelAsset* GetModelAssetTyped() const
	{
		return Cast<UCEModelAsset>(GetModelAsset());
	}

	/** Returns nullptr if service/model isn’t initialized yet. */
	const FCEModel* GetModel() const
	{
		if (const UCEModelAsset* A = GetModelAssetTyped())
		{
			return &A->GetModel();
		}
		return nullptr;
	}
};