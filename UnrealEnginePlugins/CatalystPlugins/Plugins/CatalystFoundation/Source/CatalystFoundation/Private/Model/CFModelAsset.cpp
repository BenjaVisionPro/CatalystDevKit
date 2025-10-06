/**
 * @file CFModelAsset.cpp
 * @brief Implementation for CFModelAsset.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

// ============================================
// Catalyst Foundation — Model Asset (private)
// ============================================

#include "Model/CFModelAsset.h"

#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "JsonObjectConverter.h"
#include "Misc/EngineVersion.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "Log/CFLog.h"            // CF_INFO / CF_WARN / CF_ERR
#define CF_LOG_DEFAULT_CATEGORY LogCF
#include "Log/CFLog.h"            // header-only macros (safe to include twice for default)

void UCFModelAsset::RefreshVersionMetadata() const
{
	// Schema
	const_cast<UCFModelAsset*>(this)->Version.SchemaVersion = GetSchemaVersion();

	// Engine
	const_cast<UCFModelAsset*>(this)->Version.EngineVersion = FEngineVersion::Current().ToString();

	// Plugin
	const FString PluginName = GetPluginNameForPaths();
	if (!PluginName.IsEmpty())
	{
		if (TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName))
		{
			const_cast<UCFModelAsset*>(this)->Version.PluginVersion = Plugin->GetDescriptor().VersionName;
			return;
		}
	}
	const_cast<UCFModelAsset*>(this)->Version.PluginVersion = TEXT("Unknown");
}

void UCFModelAsset::UpdateVersionMetadata() const
{
	RefreshVersionMetadata();
}

bool UCFModelAsset::ApplyJsonString(const FString& JsonText, FString& OutError)
{
	TSharedPtr<FJsonObject> Obj;
	{
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
		if (!FJsonSerializer::Deserialize(Reader, Obj) || !Obj.IsValid())
		{
			OutError = TEXT("Failed to parse JSON.");
			return false;
		}
	}

	if (UScriptStruct* S = GetPayloadScriptStruct())
	{
		if (void* Mem = GetPayloadMemory())
		{
			if (!FJsonObjectConverter::JsonObjectToUStruct(Obj.ToSharedRef(), S, Mem, 0, 0))
			{
				OutError = TEXT("JSON -> struct conversion failed.");
				return false;
			}
			return true;
		}
	}

	OutError = TEXT("Model asset did not implement payload accessors.");
	return false;
}

bool UCFModelAsset::ExportJsonString(FString& OutJson, FString& OutError) const
{
	// Ensure provenance is current
	RefreshVersionMetadata();

	if (const UScriptStruct* S = GetPayloadScriptStruct())
	{
		if (const void* Mem = GetPayloadMemory())
		{
			if (!FJsonObjectConverter::UStructToJsonObjectString(S, Mem, OutJson, 0, 0))
			{
				OutError = TEXT("Struct -> JSON conversion failed.");
				return false;
			}
			return true;
		}
	}

	OutError = TEXT("Model asset did not implement payload accessors.");
	return false;
}

FString UCFModelAsset::GetSavedJsonFile() const
{
	const FString Dir = FPaths::Combine(FPaths::ProjectSavedDir(), GetPluginNameForPaths());
	IFileManager::Get().MakeDirectory(*Dir, /*Tree*/true);
	return FPaths::Combine(Dir, TEXT("Model.json"));
}

bool UCFModelAsset::TryLoadFromDiskJson(FString& OutError)
{
	const FString File = GetSavedJsonFile();
	if (!FPaths::FileExists(File))
	{
		// No dev JSON yet -> keep asset defaults
		return true;
	}

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *File))
	{
		OutError = FString::Printf(TEXT("Failed to read %s"), *File);
		return false;
	}

	return ApplyJsonString(JsonText, OutError);
}

bool UCFModelAsset::SaveToDiskJson(FString& OutError) const
{
	// Ensure provenance is current
	RefreshVersionMetadata();

	FString JsonText;
	if (!ExportJsonString(JsonText, OutError))
	{
		return false; // OutError already set
	}

	const FString File = GetSavedJsonFile();
	if (!FFileHelper::SaveStringToFile(JsonText, *File))
	{
		OutError = FString::Printf(TEXT("Failed to write %s"), *File);
		return false;
	}

	CF_INFO(TEXT("Saved dev JSON: %s"), *File);
	return true;
}