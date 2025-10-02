#include "Model/CFAbstractObject.h"

UCFAbstractObject::UCFAbstractObject()
{
	EnsureId();
}

void UCFAbstractObject::EnsureId()
{
	if (!Id.IsValid())
	{
		Id = FGuid::NewGuid();
	}
}

void UCFAbstractObject::PostLoad()
{
	Super::PostLoad();
	EnsureId();
}

#if WITH_EDITOR
void UCFAbstractObject::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
}

void UCFAbstractObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif