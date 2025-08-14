#pragma once

#include "CoreMinimal.h"

namespace BVC
{
    struct FBVCParsedUrl
    {
        FString Scheme;   // "ws","wss","http","https","tcp", etc. (lowercased)
        FString Host;     // hostname or IP
        int32   Port = 0; // 0 if absent (callers can substitute defaults)
        FString Path;     // begins with '/', or empty
        FString Query;    // without leading '?'
        FString Fragment; // without leading '#'
        bool    bValid = false;
    };

    /** Return default port for common schemes; 0 if unknown. */
    inline int32 DefaultPortForScheme(const FString& SchemeLower)
    {
        if (SchemeLower == TEXT("ws"))   return 80;
        if (SchemeLower == TEXT("wss"))  return 443;
        if (SchemeLower == TEXT("http")) return 80;
        if (SchemeLower == TEXT("https"))return 443;
        if (SchemeLower == TEXT("tcp"))  return 0;   // explicit or negotiated
        return 0;
    }

    /** Parse "<scheme>://host[:port][/path][?query][#fragment]". Very small, no IPv6 brackets support (add later if needed). */
    CATALYSTCONNECT_API bool ParseUrl(const FString& InUrl, FBVCParsedUrl& Out);
}