// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CFModelAsset.generated.h"

/**
 * UCFModelAsset
 * A typed UPrimaryDataAsset that hosts a plugin’s root UStruct model and provides
 * minimal JSON load/save helpers. Concrete subclasses implement the three protected
 * accessors to expose their root struct and memory.
 *
 * Plugin subclass overrides:
 *  - GetPluginNameForPaths()   -> "CatalystEcosystem" (used for Saved/<Plugin>/Model.json)
 *  - GetPayloadScriptStruct()  -> StaticStruct() of your root UStruct
 *  - GetPayloadMemory()        -> &YourRootStruct (const + non-const versions)
 *
 * Public helpers:
 *  - ApplyJsonString(...)      -> import JSON text into the struct
 *  - ExportJsonString(...)     -> dump struct as JSON text
 *  - TryLoadFromDiskJson(...)  -> dev convenience (Saved/<Plugin>/Model.json)
 *  - SaveToDiskJson(...)       -> write to Saved/<Plugin>/Model.json
 */
UCLASS(BlueprintType, Abstract)
class CATALYSTFOUNDATION_API UCFModelAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Optional short summary for editor/diagnostics. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSummaryText() const { return TEXT(""); }

	/** Import a JSON string into the concrete root struct. */
	bool ApplyJsonString(const FString& JsonText, FString& OutError);

	/** Export the concrete root struct to a JSON string. */
	bool ExportJsonString(FString& OutJson, FString& OutError) const;

	/** Saved/<Plugin>/Model.json path (dev convenience). */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual FString GetSavedJsonFile() const;

	/** Load JSON from Saved/<Plugin>/Model.json and apply it. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool TryLoadFromDiskJson(FString& OutError);

	/** Save current struct to Saved/<Plugin>/Model.json. */
	UFUNCTION(BlueprintCallable, Category="CF|Model")
	virtual bool SaveToDiskJson(FString& OutError) const;

protected:
	/** Plugin name segment for Saved/<Plugin>/...  (override in child assets) */
	virtual FString GetPluginNameForPaths() const { return TEXT("UnknownPlugin"); }

	/** These three power the JSON helpers. Child assets must override them. */
	virtual UScriptStruct* GetPayloadScriptStruct() const { return nullptr; }
	virtual void*          GetPayloadMemory()             { return nullptr; }
	virtual const void*    GetPayloadMemory() const       { return nullptr; }
};