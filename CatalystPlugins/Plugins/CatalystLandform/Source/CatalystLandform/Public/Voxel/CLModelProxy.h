// ============================================================================
// CLModelProxy
// Lightweight proxy to the CL data model (FCLModel), optionally bound to a
// UCLModelAsset for editor workflows. Keeps a direct pointer to the struct
// for fast runtime access, but doesn't own it.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Model/CLModel.h"          // FCLModel
#include "Model/CLModelAsset.h"     // UCLModelAsset
#include "CLModelProxy.generated.h"

UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLModelProxy final : public UObject
{
	GENERATED_BODY()

public:
	// ---------- Construction / Binding ----------

	/** Bind to an asset. The proxy will point to Asset->Model. */
	UFUNCTION(BlueprintCallable, Category="Landform|Model")
	void InitializeFromAsset(UCLModelAsset* InAsset);

	/** Clear all bindings. After this, IsValidProxy() will be false. */
	UFUNCTION(BlueprintCallable, Category="Landform|Model")
	void Clear();

	/** True if the proxy currently has a valid model pointer. */
	UFUNCTION(BlueprintPure, Category="Landform|Model")
	bool IsValidProxy() const { return ModelPtr != nullptr; }

	// ---------- Accessors (C++-centric) ----------

	/** Get const pointer to the current model, or nullptr if unbound. */
	const FCLModel* GetModel() const { return ModelPtr; }

	/** Get mutable pointer to the current model, or nullptr if unbound. */
	FCLModel* GetMutableModel() { return ModelPtr; }

	/** Get the bound asset (may be null if proxy was bound from a raw struct). */
	UFUNCTION(BlueprintPure, Category="Landform|Model")
	UCLModelAsset* GetAsset() const { return ModelAsset; }

	/** Re-sync ModelPtr from ModelAsset if needed (safe to call anytime). */
	void RefreshFromAsset();

	// ---------- Convenience (Blueprint-friendly copies) ----------

	/** Returns a copy of the model (invalid proxy => default struct). */
	UFUNCTION(BlueprintPure, Category="Landform|Model")
	FCLModel GetModelCopy() const { return ModelPtr ? *ModelPtr : FCLModel{}; }

protected:
	// Keep the UObject reference for editor workflows & hot-reload
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Landform|Model")
	TObjectPtr<UCLModelAsset> ModelAsset = nullptr;

	// Non-UObject raw pointer for fast runtime reads/writes.
	// Not a UPROPERTY on purpose: we don't want GC ownership or serialization.
	FCLModel* ModelPtr = nullptr;

	// UObject overrides to keep pointers consistent across load / editor edits
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};