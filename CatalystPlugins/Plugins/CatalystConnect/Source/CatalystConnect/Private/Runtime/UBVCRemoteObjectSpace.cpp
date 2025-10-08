#include "Runtime/UBVCRemoteObjectSpace.h"
#include "Util/BVCLogging.h"
#include "Util/BVCThreadDispatch.h"

namespace
{
    struct FSubEntry
    {
        TArray<FString> Classes;
        FName Topic;
        bool bDeliverOnGameThread = false;
    };

    // Subscriptions per object space instance: Space* -> SubId -> Entry
    static TMap<const UBVCRemoteObjectSpace*, TMap<int64, FSubEntry>> GObjectSpaceSubs;
}

FBVCSubscriptionHandle UBVCRemoteObjectSpace::Subscribe(const TArray<FString>& Classes, FName Topic, bool bDeliverOnGameThread)
{
    FBVCSubscriptionHandle Handle;
    Handle.SubId = ++LastSubId;

    FSubEntry& Entry = GObjectSpaceSubs.FindOrAdd(this).FindOrAdd(Handle.SubId);
    Entry.Classes = Classes;
    Entry.Topic = Topic;
    Entry.bDeliverOnGameThread = bDeliverOnGameThread;

    UE_LOG(LogCatalystConnect, Verbose, TEXT("ObjectSpace %p Subscribe: SubId=%lld Topic=%s Classes=%d bGT=%s"),
        this, Handle.SubId, *Topic.ToString(), Classes.Num(), bDeliverOnGameThread ? TEXT("true") : TEXT("false"));

    // Future: bind transport stream(s) here.
    return Handle;
}

void UBVCRemoteObjectSpace::Unsubscribe(FBVCSubscriptionHandle Handle)
{
    if (Handle.SubId <= 0)
    {
        UE_LOG(LogCatalystConnect, Warning, TEXT("ObjectSpace %p Unsubscribe called with invalid SubId=%lld"), this, Handle.SubId);
        return;
    }

    if (TMap<int64, FSubEntry>* MapPtr = GObjectSpaceSubs.Find(this))
    {
        const bool bRemoved = (MapPtr->Remove(Handle.SubId) > 0);
        UE_LOG(LogCatalystConnect, Verbose, TEXT("ObjectSpace %p Unsubscribe SubId=%lld (removed=%s)"),
            this, Handle.SubId, bRemoved ? TEXT("true") : TEXT("false"));

        if (MapPtr->Num() == 0)
        {
            GObjectSpaceSubs.Remove(this);
        }
    }
    else
    {
        UE_LOG(LogCatalystConnect, Verbose, TEXT("ObjectSpace %p Unsubscribe SubId=%lld (no map)"), this, Handle.SubId);
    }
}
