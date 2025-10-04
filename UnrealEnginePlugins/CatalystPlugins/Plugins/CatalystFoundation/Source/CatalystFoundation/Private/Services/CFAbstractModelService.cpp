// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Services/CFAbstractModelService.h"
#include "Model/CFModelAsset.h"

void UCFAbstractModelService::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadModel();
}

void UCFAbstractModelService::Deinitialize()
{
	Model = nullptr;
	Super::Deinitialize();
}

bool UCFAbstractModelService::LoadModel()
{
	if (!Model)
	{
		Model = InstantiateModelFromSeed();
		if (!Model)
		{
			UE_LOG(LogTemp, Error, TEXT("CF: %s: failed to instantiate model from seed."), *GetName());
			return false;
		}
	}

	FString Error;
	if (!Model->TryLoadFromDiskJson(Error))
	{
		UE_LOG(LogTemp, Warning, TEXT("CF: %s: JSON load failed: %s"), *GetName(), *Error);
	}
	return true;
}

UCFModelAsset* UCFAbstractModelService::InstantiateModelFromSeed()
{
	const TSoftObjectPtr<UCFModelAsset> SeedPtr = GetSeedModelAsset();
	if (!SeedPtr.IsNull())
	{
		if (UCFModelAsset* Seed = SeedPtr.LoadSynchronous())
		{
			// Work on a transient duplicate at runtime
			return DuplicateObject<UCFModelAsset>(Seed, this);
		}
		UE_LOG(LogTemp, Warning, TEXT("CF: %s: Seed asset not found: %s"),
			*GetName(), *SeedPtr.ToString());
	}

	// Last-ditch fallback (rare)
	return NewObject<UCFModelAsset>(this, UCFModelAsset::StaticClass());
}