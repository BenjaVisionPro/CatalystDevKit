// ============================================
// Catalyst Foundation — Model Asset (public)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CFModelAsset.generated.h"

/** Version & provenance embedded in every model asset. */
USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFModelVersionInfo
{
	GENERATED_BODY()

	/** Bumps when the *struct schema* changes. Override via GetSchemaVersion(). */
	UPROPERTY(EditAnywhere, Category="CF|Model")
	int32 SchemaVersion = 1;

	/** Copied from the owning plugin's .uplugin (VersionName). */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FString PluginVersion;

	/** Engine version that produced/last saved this asset (e.g., 5.7.0). */
	UPROPERTY(VisibleAnywhere, Category="CF|Model")
	FString EngineVersion;
};

/**
 * UCFModelAsset
 * Root data asset base for Catalyst plugins. Hosts a concrete UStruct payload and
 * provides JSON import/export + version/provenance metadata.
 *
 * Plugin subclass overrides:
 *  - GetPluginNameForPaths()   -> "CatalystEcosystem" (Saved/<Plugin>/Model.json)
 *  - GetPayloadScriptStruct()  -> StaticStruct() of your root UStruct
 *  - GetPayloadMemory()        -> &YourRootStruct (const + non-const)
 *  - GetSchemaVersion()        -> int32 schema version for your model
 */
UCLASS(BlueprintType, Abstract)
class CATALYSTFOUNDATION_API UCFModelAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Optional short summary for editor/diagnostics. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Embedded provenance. Always refreshed on export/save helpers. */
	UPROPERTY(EditAnywhere, Category="CF|Model")
	FCFModelVersionInfo Version;

	// ---------- Public JSON helpers ----------
	/** Import a JSON string into the concrete root struct. */
	bool ApplyJsonString(const FString& JsonText, FString& OutError);

	/** Export the concrete root struct to a JSON string (updates Version first). */
	bool ExportJsonString(FString& OutJson, FString& OutError) const;

	/** Saved/<Plugin>/Model.json path (dev convenience). */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSavedJsonFile() const;

	/** Load JSON from Saved/<Plugin>/Model.json and apply it. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	/** Save current struct to Saved/<Plugin>/Model.json (updates Version first). */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

	/** Public hook for tools/commandlets to refresh version metadata pre-save. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	void UpdateVersionMetadata() const;

protected:
	// ---------- Plugin identity & struct access ----------
	virtual FString      GetPluginNameForPaths() const { return TEXT("UnknownPlugin"); }
	virtual int32        GetSchemaVersion() const { return 1; }

	/** These power the JSON helpers. Child assets must override them. */
	virtual UScriptStruct* GetPayloadScriptStruct() const { return nullptr; }
	virtual void*          GetPayloadMemory()             { return nullptr; }
	virtual const void*    GetPayloadMemory() const       { return nullptr; }

	// ---------- Version/provenance maintenance ----------
	/** Refresh Version fields from plugin + engine state. Called before export/save. */
	void RefreshVersionMetadata() const;
};