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
 * One live model asset per plugin (loaded at GameInstance init).
 * - JSON (Saved/<Plugin>/Model.json) is applied first if present.
 * - Otherwise the seeded asset remains as default values.
 */
UCLASS(Abstract)
class CATALYSTFOUNDATION_API UCFAbstractModelService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Non-template, instance accessors (this is what CE calls).
	const UCFModelAsset* Get() const { return Model; }
	UCFModelAsset*       GetMutable() { return Model; }

	// Required plugin identity + seed reference.
	virtual FName GetPluginName() const PURE_VIRTUAL(UCFAbstractModelService::GetPluginName, return NAME_None;);
	virtual TSoftObjectPtr<UCFModelAsset> GetSeedModelAsset() const PURE_VIRTUAL(UCFAbstractModelService::GetSeedModelAsset, return nullptr;);

	// Subsystem lifecycle
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	bool          LoadModel();            // apply JSON if present
	UCFModelAsset* InstantiateModelFromSeed();

protected:
	UPROPERTY(Transient)
	UCFModelAsset* Model = nullptr;
};