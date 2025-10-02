#include "Model/CFModelRoot.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"

FString UCFModelRoot::GetOwningPluginName() const
{
    FString PluginName;
    if (const UPackage* Pkg = GetOutermost())
    {
        const FString PackageName = Pkg->GetName();
        TArray<FString> Segments;
        PackageName.ParseIntoArray(Segments, TEXT("/"), true);
        if (Segments.Num() > 0)
        {
            PluginName = Segments[0];
        }
    }
    if (PluginName.IsEmpty())
    {
        PluginName = GetClass()->GetOuterUPackage() ? GetClass()->GetOuterUPackage()->GetName() : TEXT("UnknownPlugin");
    }
    return PluginName;
}

FString UCFModelRoot::GetSavedJsonFile() const
{
    const FString Dir = FPaths::Combine(FPaths::ProjectSavedDir(), GetOwningPluginName());
    IFileManager::Get().MakeDirectory(*Dir, true);
    return FPaths::Combine(Dir, TEXT("Model.json"));
}

bool UCFModelRoot::ToJsonString(FString& OutJson, FString& OutError) const
{
    rapidjson::StringBuffer Buffer;
    rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
    Writer.StartObject();
    SerializeToJson(Writer);
    Writer.EndObject();
    OutJson = UTF8_TO_TCHAR(Buffer.GetString());
    return true;
}

bool UCFModelRoot::FromJsonString(const FString& InJson, FString& OutError)
{
    rapidjson::Document Doc;
    Doc.Parse(TCHAR_TO_UTF8(*InJson));
    if (Doc.HasParseError() || !Doc.IsObject())
    {
        OutError = TEXT("Invalid JSON root (parse error or not an object).");
        return false;
    }
    return DeserializeFromJson(Doc, OutError);
}

bool UCFModelRoot::TryLoadFromDiskJson(FString& OutError)
{
    const FString File = GetSavedJsonFile();
    if (!FPaths::FileExists(File))
    {
        return true;
    }
    FString Json;
    if (!FFileHelper::LoadFileToString(Json, *File))
    {
        OutError = FString::Printf(TEXT("Failed to read JSON file: %s"), *File);
        return false;
    }
    return FromJsonString(Json, OutError);
}

bool UCFModelRoot::SaveToDiskJson(FString& OutError) const
{
    FString Json;
    if (!ToJsonString(Json, OutError))
    {
        if (OutError.IsEmpty()) OutError = TEXT("ToJsonString failed.");
        return false;
    }
    const FString File = GetSavedJsonFile();
    if (!FFileHelper::SaveStringToFile(Json, *File))
    {
        OutError = FString::Printf(TEXT("Failed to write JSON file: %s"), *File);
        return false;
    }
    return true;
}
