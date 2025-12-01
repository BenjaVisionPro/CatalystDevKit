// ============================================================================
// CLModelProxy.cpp
// ============================================================================

#include "Voxel/CLModelProxy.h"

void UCLModelProxy::InitializeFromAsset(UCLModelAsset* InAsset)
{
	ModelAsset = InAsset;
	RefreshFromAsset();
}

void UCLModelProxy::Clear()
{
	ModelAsset = nullptr;
	ModelPtr   = nullptr;
}

void UCLModelProxy::RefreshFromAsset()
{
	ModelPtr = ModelAsset ? &ModelAsset->Model : nullptr;
}

void UCLModelProxy::PostLoad()
{
	Super::PostLoad();
	RefreshFromAsset();
}

#if WITH_EDITOR
void UCLModelProxy::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.Property)
	{
		RefreshFromAsset();
		return;
	}

	const FName PropName = PropertyChangedEvent.Property->GetFName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UCLModelProxy, ModelAsset))
	{
		RefreshFromAsset();
	}
}
#endif