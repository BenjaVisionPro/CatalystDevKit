// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CFAbstractModelService.generated.h"

class UCFModelAsset;

/**
 * Opinionated base:
 * - One live UCFModelAsset instance per plugin (owned by the GameInstance).
 * - On Initialize: duplicate the seed asset, then (optionally) apply dev JSON
 *   from Saved/<Plugin>/Model.json.
 * - Plugins subclass this and only implement GetPluginName() and GetSeedModelAsset().
 */
UCLASS(Abstract)
class CATALYSTFOUNDATION_API UCFAbstractModelService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Accessors used by plugins/UIs.
	const UCFModelAsset* Get() const { return Model; }
	UCFModelAsset*       GetMutable() { return Model; }

	// REQUIRED: plugin identity + seed (compile-time enforced by override).
	virtual FName GetPluginName() const PURE_VIRTUAL(UCFAbstractModelService::GetPluginName, return NAME_None;);
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const PURE_VIRTUAL(UCFAbstractModelService::GetSeedModelAsset, return nullptr;);

	// Subsystem lifecycle.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	// Create/refresh live instance; applies JSON if present.
	bool           LoadModel();
	// Duplicate the seed into a transient, runtime-owned instance.
	UCFModelAsset* InstantiateModelFromSeed();

protected:
	UPROPERTY(Transient)
	UCFModelAsset* Model = nullptr;
};