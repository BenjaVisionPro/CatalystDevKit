/**
 * @file CFModelAsset.h
 * @brief Root data-asset base for Catalyst plugins:
 *        hosts a concrete UStruct payload, handles JSON import/export,
 *        and embeds version/provenance metadata for migration and diagnostics.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Validation/CFValidatable.h"  // Standardized validation interface
#include "CFModelAsset.generated.h"

class UAssetImportData; // editor-only forward decl

/**
 * @brief Version & provenance embedded in every model asset.
 *        Updated automatically before export/save.
 */
USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFModelVersionInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="Foundation|Model")
	int32 SchemaVersion = 1;

	UPROPERTY(VisibleAnywhere, Category="Foundation|Model")
	FString PluginVersion;

	UPROPERTY(VisibleAnywhere, Category="Foundation|Model")
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
	UFUNCTION(BlueprintCallable, Category="Foundation|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Embedded provenance. */
	UPROPERTY(VisibleAnywhere, Category="Foundation|Model")
	FCFModelVersionInfo Version;

#if WITH_EDITORONLY_DATA
	/** Source data for UE's Reimport workflow (points at the JSON file). */
	UPROPERTY(VisibleAnywhere, Instanced, Category="Import", meta=(ShowOnlyInnerProperties))
	TObjectPtr<UAssetImportData> ImportData = nullptr;
#endif

	// ---------- JSON helpers ----------

	bool ApplyJsonString(const FString& JsonText, FString& OutError);
	bool ExportJsonString(FString& OutJson, FString& OutError) const;

	UFUNCTION(BlueprintCallable, Category="Foundation|Model")
	virtual FString GetSavedJsonFile() const;

	UFUNCTION(BlueprintCallable, Category="Foundation|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	UFUNCTION(BlueprintCallable, Category="Foundation|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

	UFUNCTION(BlueprintCallable, Category="Foundation|Model")
	void UpdateVersionMetadata() const;

	// ---------- Public accessors (editor-safe) ----------

	int32   GetPublicSchemaVersion() const { return GetSchemaVersion(); }
	FString GetPublicPluginNameForPaths() const { return GetPluginNameForPaths(); }

protected:
	// ---------- Plugin identity & struct access ----------

	virtual FString      GetPluginNameForPaths() const { return TEXT("UnknownPlugin"); }
	virtual int32        GetSchemaVersion() const { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const { return nullptr; }
	virtual void*          GetPayloadMemory()             { return nullptr; }
	virtual const void*    GetPayloadMemory() const       { return nullptr; }

	// ---------- Validation seam ----------

	virtual void NormalizePayload() {}
	virtual bool ValidatePayload(FString& OutError) const { return true; }
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;

	// ---------- Version/provenance ----------
	void RefreshVersionMetadata() const;

#if WITH_EDITOR
	/** Ensure ImportData exists and points at our JSON (used by export/reimport). */
	void EnsureImportDataUpToDate(const FString& SourceJsonPath);
#endif
};