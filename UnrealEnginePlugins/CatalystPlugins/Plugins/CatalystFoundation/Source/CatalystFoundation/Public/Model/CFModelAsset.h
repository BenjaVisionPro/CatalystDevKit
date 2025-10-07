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
#include "Validation/CFValidatable.h"  // Standardized validation interface
#include "CFModelAsset.generated.h"

/**
 * @brief Version & provenance embedded in every model asset.
 *        Updated automatically before export/save.
 */
USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFModelVersionInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	int32 SchemaVersion = 1;

	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FString PluginVersion;

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
 *  - NormalizePayload() / ValidatePayload() → per-plugin rules
 *  - CollectValidationMessages() → structured results for editor/CI
 */
UCLASS(BlueprintType, Abstract)
class CATALYSTFOUNDATION_API UCFModelAsset
	: public UPrimaryDataAsset
	, public ICFValidatable
{
	GENERATED_BODY()

public:
	// ---------- Summary / metadata ----------

	/** Optional short summary for editor/diagnostics. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Embedded provenance. */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FCFModelVersionInfo Version;

	// ---------- JSON helpers ----------

	bool ApplyJsonString(const FString& JsonText, FString& OutError);
	bool ExportJsonString(FString& OutJson, FString& OutError) const;

	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSavedJsonFile() const;

	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

	UFUNCTION(BlueprintCallable, Category="CF|Model")
	void UpdateVersionMetadata() const;

	// ---------- Public accessors (editor-safe) ----------

	/** Public bridge for editor widgets (avoids protected access warnings). */
	int32 GetPublicSchemaVersion() const { return GetSchemaVersion(); }

	/** Public bridge for editor widgets (avoids protected access warnings). */
	FString GetPublicPluginNameForPaths() const { return GetPluginNameForPaths(); }

protected:
	// ---------- Plugin identity & struct access ----------

	virtual FString      GetPluginNameForPaths() const { return TEXT("UnknownPlugin"); }
	virtual int32        GetSchemaVersion() const { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const { return nullptr; }
	virtual void*          GetPayloadMemory()             { return nullptr; }
	virtual const void*    GetPayloadMemory() const       { return nullptr; }

	// ---------- Validation seam ----------

	/** Normalize payload (sorting, range clamping, filling defaults). */
	virtual void NormalizePayload() {}

	/** Validate payload invariants (legacy single-string version). */
	virtual bool ValidatePayload(FString& OutError) const { return true; }

	/** Structured validation messages for editor / CI. */
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;

	// ---------- Version/provenance ----------
	void RefreshVersionMetadata() const;
};