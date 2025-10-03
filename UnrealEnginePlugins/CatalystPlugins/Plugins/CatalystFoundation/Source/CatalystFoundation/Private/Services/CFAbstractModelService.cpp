#include "Services/CFAbstractModelService.h"
#include "Model/CFModelAsset.h"
#include "Engine/AssetManager.h"
#include "UObject/UObjectGlobals.h"

void UCFAbstractModelService::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadModel();
}

void UCFAbstractModelService::Deinitialize()
{
	ModelAsset = nullptr;
	Super::Deinitialize();
}

bool UCFAbstractModelService::LoadModel()
{
	// Ensure instance exists
	if (!ModelAsset)
	{
		ModelAsset = InstantiateModelFromSeed();
		if (!ModelAsset)
		{
			UE_LOG(LogTemp, Error, TEXT("CF: %s: failed to instantiate model asset from seed."), *GetName());
			return false;
		}
	}

	// Overlay from Saved/<Plugin>/Model.json (non-fatal if absent)
	FString Error;
	if (!ModelAsset->TryLoadFromDiskJson(Error))
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
			return DuplicateObject<UCFModelAsset>(Seed, this); // transient runtime copy
		}
		UE_LOG(LogTemp, Warning, TEXT("CF: %s: Seed asset not found: %s"), *GetName(), *SeedPtr.ToString());
	}

	// Fallback (rare): plain base instance
	return NewObject<UCFModelAsset>(this, UCFModelAsset::StaticClass());
}