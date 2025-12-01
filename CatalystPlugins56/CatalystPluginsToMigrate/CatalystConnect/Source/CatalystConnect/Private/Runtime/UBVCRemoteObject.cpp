#include "Runtime/UBVCRemoteObject.h"
#include "Util/BVCThreadDispatch.h"

bool UBVCRemoteObject::GetStringField(FName Field, FString& Out) const
{
    if (const FBVCValue* V = Fields.Find(Field))
    {
        if (V->Type == EBVCValueType::String)
        {
            Out = V->String;
            return true;
        }
    }
    return false;
}

bool UBVCRemoteObject::SetStringField(FName Field, const FString& In)
{
    Fields.Add(Field, FBVCValue::MakeString(In));

    // Raise patch on the game thread for BP safety.
    const FGuid LocalId = Id;
    BVC::EnqueueOnGameThread([this, LocalId]()
    {
        OnRemotePatched.Broadcast(LocalId);
    });

    return true;
}
