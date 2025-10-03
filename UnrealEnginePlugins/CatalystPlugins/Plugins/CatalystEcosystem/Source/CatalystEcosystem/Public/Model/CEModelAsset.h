// ============================================
// CE: Model Asset (wrapper around FCEModel)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"      // from Foundation
#include "Model/CEModel.h"
#include "CEModelAsset.generated.h"

/**
 * UCEModelAsset
 * -------------
 * Asset wrapper that holds the CE root struct (FCEModel).
 * - Implements the “model struct accessors” required by UCFModelAsset.
 * - Provides a typed accessor GetModel().
 */
UCLASS(BlueprintType)
class CATALYSTECOSYSTEM_API UCEModelAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	/** Typed, read-only access to the model struct. */
	const FCEModel& GetModel() const { return Model; }
	/** Optional mutable access if you need to modify via tools. */
	FCEModel&       GetMutableModel() { return Model; }

	// Summary shown in editor / diagnostics
	virtual FString GetSummaryText() const override;

protected:
	// Implement the Foundation JSON helper hooks
	virtual UScriptStruct* GetModelStructType() const override { return FCEModel::StaticStruct(); }
	virtual void*          GetModelStructMemory()       override { return &Model; }
	virtual const void*    GetModelStructMemory() const override { return &Model; }

private:
	UPROPERTY(EditAnywhere, Category="CE|Model")
	FCEModel Model;
};