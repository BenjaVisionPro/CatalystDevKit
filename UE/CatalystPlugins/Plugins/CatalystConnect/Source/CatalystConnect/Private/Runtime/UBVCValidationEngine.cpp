#include "Runtime/UBVCValidationEngine.h"
#include "Schema/FBVCMADescription.h"

namespace
{
    static const FBVCMAAttribute* FindAttribute(const FBVCMADescription& Desc, FName Field)
    {
        const FString Wanted = Field.ToString();
        for (const FBVCMAAttribute& Attr : Desc.Attributes)
        {
            if (Attr.Name == Wanted)
            {
                return &Attr;
            }
        }
        return nullptr;
    }

    static void AddIssue(TArray<FBVCValidationIssue>& OutIssues,
                         const FString& FieldPath,
                         const FString& Code,
                         const FString& Message)
    {
        FBVCValidationIssue Issue;
        Issue.FieldPath   = FieldPath;
        Issue.MessageCode = Code;
        Issue.Message     = Message;
        OutIssues.Add(MoveTemp(Issue));
    }

    static bool IsEffectivelyEmpty(const FBVCMAAttribute& Attr, const FString& AsText)
    {
        if (Attr.Kind == EBVCMAKind::Scalar &&
            (Attr.ScalarType == EBVCMAScalarType::String || Attr.ScalarType == EBVCMAScalarType::Name))
        {
            return AsText.TrimStartAndEnd().IsEmpty();
        }
        return AsText.IsEmpty();
    }
}

bool UBVCValidationEngine::ValidateField(const FBVCMADescription& Description,
                                         FName Field,
                                         const FString& Value,
                                         TArray<FBVCValidationIssue>& OutIssues) const
{
    const FBVCMAAttribute* Attr = FindAttribute(Description, Field);
    if (!Attr)
    {
        // Unknown field — let the server handle this
        return true;
    }

    const bool bEmpty = IsEffectivelyEmpty(*Attr, Value);

    // Respect bNullable even without explicit Required validator
    if (!Attr->bNullable && bEmpty)
    {
        AddIssue(OutIssues, Field.ToString(), TEXT("required"), TEXT("Value is required."));
        return false;
    }

    // Scan explicit validator specs — v1 only implements Required
    for (const FBVCMAValidatorSpec& V : Attr->Validators)
    {
        if (V.Type == EBVCMAValidatorType::Required && bEmpty)
        {
            AddIssue(OutIssues,
                     Field.ToString(),
                     V.MessageCode.IsEmpty() ? TEXT("required") : V.MessageCode,
                     V.Message.IsEmpty() ? TEXT("Value is required.") : V.Message);
            return false;
        }
        // TODO: Length, Range, Regex, Enumeration, CrossField, UniqueInArray, CustomRef
    }

    return true;
}

bool UBVCValidationEngine::ValidateObject(const FBVCMADescription& Description,
                                          TArray<FBVCValidationIssue>& OutIssues) const
{
    // No object data here yet — future: accept a map of field->text and iterate
    return true;
}
