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
	Model = nullptr; // transient; GC will handle the duplicate
	Super::Deinitialize();
}

bool UCFAbstractModelService::LoadModel()
{
	// Ensure we have a live instance first.
	if (!Model)
	{
		Model = InstantiateModelFromSeed();
		if (!Model)
		{
			UE_LOG(LogTemp, Error, TEXT("CF: %s: failed to instantiate model from seed."), *GetName());
			return false;
		}
	}

	// Best-effort dev override: Saved/<Plugin>/Model.json
	FString Error;
	if (!Model->TryLoadFromDiskJson(Error))
	{
		// Not fatal: just keep the seed defaults if JSON missing/invalid.
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
			// Work on a transient copy at runtime (we never mutate the content asset).
			return DuplicateObject<UCFModelAsset>(Seed, this);
		}

		UE_LOG(LogTemp, Warning, TEXT("CF: %s: Seed asset not found: %s"),
			*GetName(), *SeedPtr.ToString());
	}

	// Last-resort fallback: construct a bare UCFModelAsset (unlikely path).
	return NewObject<UCFModelAsset>(this, UCFModelAsset::StaticClass());
}