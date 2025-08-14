#include "Schema/Loaders/UBVCSchemaLoaderJson.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

bool UBVCSchemaLoaderJson::LoadFromJsonString(const FString& Json, FBVCMADescriptionContainer& OutContainer) const
{
    OutContainer = FBVCMADescriptionContainer(); // reset

    TSharedPtr<FJsonObject> RootObj;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (!FJsonSerializer::Deserialize(Reader, RootObj) || !RootObj.IsValid())
    {
        return false;
    }

    // Prefer the generic converter so we don’t hardcode fields here.
    if (!FJsonObjectConverter::JsonObjectToUStruct(RootObj.ToSharedRef(), &OutContainer, 0, 0))
    {
        return false;
    }

    // Minimal sanity: must have at least identifiers and descriptions present (may be empty array).
    if (!OutContainer.CatalogId.IsValid())
    {
        // If JSON omitted CatalogId, we’ll generate one (safe client-side).
        OutContainer.CatalogId = FGuid::NewGuid();
    }

    return true;
}
