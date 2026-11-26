#include "Model/CFObject.h"

FCFViewDescription FCFObject::MagritteDescription() const
{
    return {};
}

UWidget* FCFObject::AsView(const FCFViewContext& Context) const
{
    const FCFViewDescription Description = MagritteDescription();
    return Description.Container && Description.Build
        ? Description.Build(*this, *Description.Container, Context)
        : nullptr;
}

FCFIdentifiableObject::FCFIdentifiableObject()
    : FCFIdentifiableObject(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower))
{
}

FCFIdentifiableObject::FCFIdentifiableObject(FString InIdentifier)
    : Identifier(MoveTemp(InIdentifier))
{
}
