/**
 * @file CFModelAsset.h
 * @brief Root data-asset base for Catalyst plugins:
 *        hosts a concrete UStruct payload, handles JSON import/export,
 *        and embeds version/provenance metadata for migration and diagnostics.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CFModelAsset.generated.h"

/**
 * @brief Version & provenance embedded in every model asset.
 *        Updated automatically before export/save.
 */
USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFModelVersionInfo
{
	GENERATED_BODY()

	/** Bumps when the *struct schema* changes. Override via GetSchemaVersion(). */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	int32 SchemaVersion = 1;

	/** Copied from the owning plugin's .uplugin (VersionName). */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FString PluginVersion;

	/** Engine version that produced/last saved this asset (e.g. "5.7.0"). */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FString EngineVersion;
};

/**
 * @brief Foundation model asset base. Plugins subclass this, provide a root payload struct,
 *        and optional convenience paths/versions for JSON dev flows.
 *
 * Subclasses should override:
 *  - GetPluginNameForPaths()   → "CatalystEcosystem" (Saved/<Plugin>/Model.json)
 *  - GetPayloadScriptStruct()  → StaticStruct() for the root UStruct
 *  - GetPayloadMemory()        → address of the root struct (const and non-const)
 *  - GetSchemaVersion()        → current schema integer for migrations
 *  - (optional) NormalizePayload() / ValidatePayload() → per-plugin rules
 */
UCLASS(BlueprintType, Abstract)
class CATALYSTFOUNDATION_API UCFModelAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Optional short summary for editor/diagnostics. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Embedded provenance. Refreshed on export/save helpers. */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FCFModelVersionInfo Version;

	// ---------- JSON helpers ----------

	/**
	 * @brief Import a JSON string into the concrete root struct.
	 *        On success: NormalizePayload() then ValidatePayload() are invoked.
	 * @return true on success; false sets OutError.
	 */
	bool ApplyJsonString(const FString& JsonText, FString& OutError);

	/**
	 * @brief Export the concrete root struct to a JSON string.
	 *        Refreshes Version metadata first, then ValidatePayload().
	 * @return true on success; false sets OutError.
	 */
	bool ExportJsonString(FString& OutJson, FString& OutError) const;

	/** @return Saved/<Plugin>/Model.json (dev convenience). Creates directory on demand. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSavedJsonFile() const;

	/**
	 * @brief Load JSON from Saved/<Plugin>/Model.json and apply it.
	 * @note Missing file is treated as success (asset defaults remain).
	 */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	/**
	 * @brief Save current struct to Saved/<Plugin>/Model.json.
	 *        Refreshes Version first and writes atomically (temp → move).
	 *        Calls ValidatePayload() before writing.
	 */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

	/** Public hook for tools/commandlets to refresh version metadata pre-save. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	void UpdateVersionMetadata() const;

protected:
	// ---------- Plugin identity & struct access ----------

	/** Plugin folder name used for Saved/<Plugin> paths. */
	virtual FString      GetPluginNameForPaths() const { return TEXT("UnknownPlugin"); }

	/** Schema integer used to detect migrations. */
	virtual int32        GetSchemaVersion() const { return 1; }

	/** These power the JSON helpers. Child assets must override them. */
	virtual UScriptStruct* GetPayloadScriptStruct() const { return nullptr; }
	virtual void*          GetPayloadMemory()             { return nullptr; }
	virtual const void*    GetPayloadMemory() const       { return nullptr; }

	// ---------- Validation seam (tiny and first-class) ----------

	/**
	 * @brief Deterministically normalize payload after import (e.g., sort arrays,
	 *        clamp ranges, fill defaults). No-ops by default.
	 * @note Keep this fast and idempotent. Called only on mutation paths.
	 */
	virtual void NormalizePayload() {}

	/**
	 * @brief Validate payload invariants. Return false with OutError on violation.
	 * @note Called after import and before export/save. Keep side-effect free.
	 */
	virtual bool ValidatePayload(FString& OutError) const { return true; }

	// ---------- Version/provenance maintenance ----------

	/** Refresh Version fields from plugin + engine state. Called before export/save. */
	void RefreshVersionMetadata() const;
};