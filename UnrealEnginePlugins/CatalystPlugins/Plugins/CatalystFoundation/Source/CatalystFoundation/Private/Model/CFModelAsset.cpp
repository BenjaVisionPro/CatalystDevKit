// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Model/CFModelAsset.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

/* ---------- Public helpers ---------- */

bool UCFModelAsset::ApplyJsonString(const FString& JsonText, FString& OutError)
{
	TSharedPtr<FJsonObject> Obj;
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
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
			if (!FJsonObjectConverter::JsonObjectToUStruct(Obj.ToSharedRef(), S, Mem, /*CheckFlags*/0, /*SkipFlags*/0))
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
	if (const UScriptStruct* S = GetPayloadScriptStruct())
	{
		if (const void* Mem = GetPayloadMemory())
		{
			if (!FJsonObjectConverter::UStructToJsonObjectString(S, Mem, OutJson, /*CheckFlags*/0, /*SkipFlags*/0))
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

/* ---------- Dev file helpers ---------- */

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
	FString JsonText;
	if (!ExportJsonString(JsonText, OutError))
	{
		return false;
	}

	const FString File = GetSavedJsonFile();
	if (!FFileHelper::SaveStringToFile(JsonText, *File))
	{
		OutError = FString::Printf(TEXT("Failed to write %s"), *File);
		return false;
	}
	return true;
}