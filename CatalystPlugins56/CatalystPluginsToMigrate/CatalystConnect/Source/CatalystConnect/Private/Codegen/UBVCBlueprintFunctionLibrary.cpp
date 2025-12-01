#include "Codegen/UBVCBlueprintFunctionLibrary.h"
#include "Runtime/UBVCRemoteObject.h"

bool UBVCBlueprintFunctionLibrary::GetStringField(UBVCRemoteObject* Obj, FName Field, FString& Out)
{
    return Obj ? Obj->GetStringField(Field, Out) : false;
}
