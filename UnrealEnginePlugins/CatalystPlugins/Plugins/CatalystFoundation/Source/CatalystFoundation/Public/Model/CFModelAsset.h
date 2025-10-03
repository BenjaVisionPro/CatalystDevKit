// ============================================
// Foundation: Model Asset (wrapper)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CFModelAsset.generated.h"

/**
 * UCFModelAsset
 * --------------
 * Opinionated base for plugin “model assets”.
 * - Holds a *struct* model internally (the real data you edit/read).
 * - Provides optional JSON load/save helpers for development.
 * - Child classes (per plugin) expose their concrete struct and memory.
 *
 * This is *not* the model itself — it’s an asset wrapper around it.
 */
UCLASS(BlueprintType, Abstract)
class CATALYSTFOUNDATION_API UCFModelAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Short human-readable summary for editor/diagnostics (safe to leave empty). */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Saved/<Plugin>/Model.json (created on demand). */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSavedJsonFile() const;

	/** Load JSON into the model struct (if file exists). Returns true on success. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	/** Save the model struct to JSON. Returns true on success. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

protected:
	/** Choose the directory name under Saved/. Default: heuristics from package name. */
	virtual FString GetPluginNameForPaths() const;

	/** Child classes must expose their root *struct* type + memory for JSON conversion. */
	virtual UScriptStruct* GetModelStructType()        const { return nullptr; }
	virtual void*          GetModelStructMemory()            { return nullptr; }
	virtual const void*    GetModelStructMemory()      const { return nullptr; }
};