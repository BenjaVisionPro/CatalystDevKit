#include "Model/CFModelAsset.h"

#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

FString UCFModelAsset::GetPluginNameForPaths() const
{
	// Heuristic: "/<Plugin>/..." -> "<Plugin>"
	if (const UPackage* Pkg = GetOutermost())
	{
		TArray<FString> Segs;
		Pkg->GetName().ParseIntoArray(Segs, TEXT("/"), /*CullEmpty*/true);
		if (Segs.Num() > 0)
		{
			return Segs[0];
		}
	}
	return TEXT("UnknownPlugin");
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
		// No file yet: keep asset defaults.
		return true;
	}

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *File))
	{
		OutError = FString::Printf(TEXT("Failed to read %s"), *File);
		return false;
	}

	TSharedPtr<FJsonObject> Obj;
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
		if (!FJsonSerializer::Deserialize(Reader, Obj) || !Obj.IsValid())
		{
			OutError = TEXT("Failed to parse JSON.");
			return false;
		}
	}

	UScriptStruct* StructType = GetModelStructType();
	void*          StructMem  = GetModelStructMemory();
	if (!StructType || !StructMem)
	{
		OutError = TEXT("Model accessors not implemented.");
		return false;
	}

	if (!FJsonObjectConverter::JsonObjectToUStruct(Obj.ToSharedRef(), StructType, StructMem, /*CheckFlags*/0, /*SkipFlags*/0))
	{
		OutError = TEXT("JSON -> struct conversion failed.");
		return false;
	}

	return true;
}

bool UCFModelAsset::SaveToDiskJson(FString& OutError) const
{
	const UScriptStruct* StructType = GetModelStructType();
	const void*          StructMem  = GetModelStructMemory();
	if (!StructType || !StructMem)
	{
		OutError = TEXT("Model accessors not implemented.");
		return false;
	}

	FString JsonText;
	if (!FJsonObjectConverter::UStructToJsonObjectString(StructType, StructMem, JsonText, /*CheckFlags*/0, /*SkipFlags*/0))
	{
		OutError = TEXT("Struct -> JSON conversion failed.");
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