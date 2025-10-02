#pragma once

#include "CoreMinimal.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"
#include "ThirdParty/rapidjson/include/rapidjson/writer.h"
#include "ThirdParty/rapidjson/include/rapidjson/stringbuffer.h"
#include "CFJson.generated.h"

UCLASS()
class CATALYSTFOUNDATION_API UCFJson : public UObject
{
    GENERATED_BODY()
public:
    static void WriteString(rapidjson::Writer<rapidjson::StringBuffer>& W, const TCHAR* Name, const FString& Value)
    {
        W.Key(TCHAR_TO_UTF8(Name));
        W.String(TCHAR_TO_UTF8(*Value));
    }

    static void WriteGuid(rapidjson::Writer<rapidjson::StringBuffer>& W, const TCHAR* Name, const FGuid& Value)
    {
        W.Key(TCHAR_TO_UTF8(Name));
        W.String(TCHAR_TO_UTF8(*Value.ToString(EGuidFormats::DigitsWithHyphens)));
    }

    static bool ReadString(const rapidjson::Value& Obj, const TCHAR* Name, FString& Out)
    {
        auto it = Obj.FindMember(TCHAR_TO_UTF8(Name));
        if (it == Obj.MemberEnd() || !it->value.IsString()) return false;
        Out = UTF8_TO_TCHAR(it->value.GetString());
        return true;
    }

    static bool ReadGuid(const rapidjson::Value& Obj, const TCHAR* Name, FGuid& Out)
    {
        FString Tmp;
        if (!ReadString(Obj, Name, Tmp)) return false;
        return FGuid::Parse(Tmp, Out);
    }
};
