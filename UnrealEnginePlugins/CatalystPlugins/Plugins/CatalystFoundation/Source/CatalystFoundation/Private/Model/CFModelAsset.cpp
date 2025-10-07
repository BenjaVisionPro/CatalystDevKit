/**
 * @file CFModelAsset.cpp
 * @brief Implementation for the foundation model asset base (JSON + provenance + validation seam).
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

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
#include "Validation/CFValidationTypes.h"

#define CF_LOG_DEFAULT_CATEGORY LogCF
#include "Log/CFLog.h" // CF_INFO / CF_WARN / CF_ERR

void UCFModelAsset::RefreshVersionMetadata() const
{
	const_cast<UCFModelAsset*>(this)->Version.SchemaVersion = GetSchemaVersion();
	const_cast<UCFModelAsset*>(this)->Version.EngineVersion = FEngineVersion::Current().ToString();

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
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);

	if (!FJsonSerializer::Deserialize(Reader, Obj) || !Obj.IsValid())
	{
		OutError = TEXT("Failed to parse JSON.");
		return false;
	}

	if (UScriptStruct* S = GetPayloadScriptStruct())
	{
		if (void* Mem = GetPayloadMemory())
		{
			if (!FJsonObjectConverter::JsonObjectToUStruct(Obj.ToSharedRef(), S, Mem, 0, 0))
			{
				OutError = TEXT("JSON → struct conversion failed.");
				return false;
			}

			NormalizePayload();
			if (!ValidatePayload(OutError))
			{
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
	RefreshVersionMetadata();

	if (!ValidatePayload(OutError))
	{
		return false;
	}

	if (const UScriptStruct* S = GetPayloadScriptStruct())
	{
		if (const void* Mem = GetPayloadMemory())
		{
			if (!FJsonObjectConverter::UStructToJsonObjectString(S, Mem, OutJson, 0, 0))
			{
				OutError = TEXT("Struct → JSON conversion failed.");
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
	IFileManager::Get().MakeDirectory(*Dir, true);
	return FPaths::Combine(Dir, TEXT("Model.json"));
}

bool UCFModelAsset::TryLoadFromDiskJson(FString& OutError)
{
	const FString File = GetSavedJsonFile();
	if (!FPaths::FileExists(File))
	{
		return true; // defaults OK
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
	RefreshVersionMetadata();

	FString JsonText;
	if (!ExportJsonString(JsonText, OutError))
	{
		return false;
	}

	const FString FinalFile = GetSavedJsonFile();
	const FString TempFile = FinalFile + TEXT(".tmp");

	if (!FFileHelper::SaveStringToFile(JsonText, *TempFile))
	{
		OutError = FString::Printf(TEXT("Failed to write %s"), *TempFile);
		return false;
	}

	const bool bMoved = IFileManager::Get().Move(*FinalFile, *TempFile, true, false, false);
	if (!bMoved)
	{
		IFileManager::Get().Delete(*TempFile, false, true);
		OutError = FString::Printf(TEXT("Failed to move %s → %s"), *TempFile, *FinalFile);
		return false;
	}

	CF_INFO(TEXT("Saved dev JSON: %s"), *FinalFile);
	return true;
}

void UCFModelAsset::CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const
{
	// Base invariant checks shared across all plugin models.
	if (!GetPayloadScriptStruct() || !GetPayloadMemory())
	{
		OutMessages.Add(FCFValidationMessage::Make(
			ECFValidationSeverity::Error, TEXT("Model.PayloadMissing"),
			NSLOCTEXT("CF", "Val_PayloadMissing", "Model payload is not bound."),
			NSLOCTEXT("CF", "Val_PayloadMissingDetail", "GetPayloadScriptStruct() or GetPayloadMemory() returned null."),
			TEXT("/Model")));
	}

	if (Version.EngineVersion.IsEmpty() || Version.PluginVersion.IsEmpty())
	{
		OutMessages.Add(FCFValidationMessage::Make(
			ECFValidationSeverity::Warning, TEXT("Model.VersionUninitialized"),
			NSLOCTEXT("CF", "Val_VersionUninitialized", "Version metadata has not been refreshed."),
			NSLOCTEXT("CF", "Val_VersionUninitializedDetail", "Call UpdateVersionMetadata() before saving."),
			TEXT("/Version"),
			NSLOCTEXT("CF", "Val_VersionUninitializedFix", "Save or export the asset to refresh metadata.")));
	}
}