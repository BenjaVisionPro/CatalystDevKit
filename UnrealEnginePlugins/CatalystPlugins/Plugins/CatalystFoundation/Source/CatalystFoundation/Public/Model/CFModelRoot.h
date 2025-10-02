#pragma once

#include "Engine/PrimaryDataAsset.h"
#include "Model/Json/CFJson.h"
#include "CFModelRoot.generated.h"

UCLASS(Abstract, BlueprintType)
class CATALYSTFOUNDATION_API UCFModelRoot : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    bool TryLoadFromDiskJson(FString& OutError);
    bool SaveToDiskJson(FString& OutError) const;

    bool ToJsonString(FString& OutJson, FString& OutError) const;
    bool FromJsonString(const FString& InJson, FString& OutError);

protected:
    virtual void SerializeToJson(rapidjson::Writer<rapidjson::StringBuffer>& Writer) const PURE_VIRTUAL(UCFModelRoot::SerializeToJson, );
    virtual bool DeserializeFromJson(const rapidjson::Value& RootObj, FString& OutError) PURE_VIRTUAL(UCFModelRoot::DeserializeFromJson, return false;);

    FString GetSavedJsonFile() const;
    FString GetOwningPluginName() const;
};
