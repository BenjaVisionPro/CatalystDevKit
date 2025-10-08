#include "Transport/BVCUrl.h"

namespace
{
    // Helper: split at first occurrence of C; returns {Left, RightAfterC}
    static void SplitOnce(const FString& S, TCHAR C, FString& Left, FString& Right)
    {
        int32 Idx;
        if (S.FindChar(C, Idx))
        {
            Left  = S.Left(Idx);
            Right = S.Mid(Idx + 1);
        }
        else
        {
            Left = S;
            Right.Reset();
        }
    }
}

namespace BVC
{
    bool ParseUrl(const FString& InUrl, FBVCParsedUrl& Out)
    {
        Out = FBVCParsedUrl();

        if (InUrl.IsEmpty())
            return false;

        FString Url = InUrl.TrimStartAndEnd();

        // scheme://rest
        int32 Colon = INDEX_NONE;
        if (!Url.FindChar(TEXT(':'), Colon) || Colon <= 0)
            return false;

        if (Url.Len() < Colon + 3 || Url.Mid(Colon, 3) != TEXT("://"))
            return false;

        Out.Scheme = Url.Left(Colon).ToLower();
        FString Rest = Url.Mid(Colon + 3); // after "://"

        // host[:port][/...]
        FString HostPort, Remainder;
        int32 Slash = INDEX_NONE;
        if (Rest.FindChar(TEXT('/'), Slash))
        {
            HostPort  = Rest.Left(Slash);
            Remainder = Rest.Mid(Slash); // includes the '/'
        }
        else
        {
            HostPort  = Rest;
            Remainder = TEXT("");
        }

        // host[:port]
        FString PortStr;
        SplitOnce(HostPort, TEXT(':'), Out.Host, PortStr);
        if (Out.Host.IsEmpty())
            return false;

        if (!PortStr.IsEmpty())
        {
            Out.Port = FCString::Atoi(*PortStr);
        }

        // path[?query][#fragment]
        FString PathAndMore = Remainder;

        // fragment
        FString NoFrag;
        SplitOnce(PathAndMore, TEXT('#'), NoFrag, Out.Fragment);

        // query
        SplitOnce(NoFrag, TEXT('?'), Out.Path, Out.Query);

        // Ensure path starts with '/' (if present at all)
        if (!Out.Path.IsEmpty() && Out.Path[0] != TEXT('/'))
        {
            Out.Path = TEXT("/") + Out.Path;
        }

        // Default port if missing
        if (Out.Port == 0)
        {
            Out.Port = DefaultPortForScheme(Out.Scheme);
        }

        Out.bValid = true;
        return true;
    }
}