#include "Voxel/Components/CLVoxelWorldComponent.h"

#include "CLVoxelWorldManager.h"

#include "VoxelWorld.h"
#include "Engine/World.h"

UCLVoxelWorldComponent::UCLVoxelWorldComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

const AVoxelWorld* UCLVoxelWorldComponent::GetVoxelWorldOwner() const
{
	return Cast<AVoxelWorld>(GetOwner());
}

TSharedPtr<const FCLWorldRuntime> UCLVoxelWorldComponent::BuildWorldRuntime() const
{
	VOXEL_FUNCTION_COUNTER();

	const UCLPlanetModelAsset* WorldAsset = CLWorldAsset.LoadSynchronous();
	const UCLStrataAsset* Strata = StrataAsset.LoadSynchronous();

	if (!WorldAsset)
	{
		return nullptr;
	}

	TSharedRef<FCLWorldRuntime> Runtime = MakeShared<FCLWorldRuntime>();

	// World band
	Runtime->InnerRadiusM = WorldAsset->Model.GetInnerRadiusM();
	Runtime->WorldHeightM = WorldAsset->Model.VoxelWorldHeightM;

	// Coord space
	Runtime->CoordSpace = CoordSpace;
	Runtime->SeamBlendWidthN = SeamBlendWidthN;

	// Determinism
	Runtime->Seed = Seed;

	// Strata
	if (Strata)
	{
		Runtime->Strata = Strata->Strata;
	}

	// Optional precompute LUT (normalized)
	Runtime->StrataLutResolution = FMath::Max(0, StrataLutResolution);
	if (Runtime->StrataLutResolution > 0 && Strata)
	{
		const int32 Res = Runtime->StrataLutResolution;
		Runtime->StrataLut.SetNum(Res + 1);

		for (int32 i = 0; i <= Res; i++)
		{
			const double AltitudeN = double(i) / double(Res);
			Runtime->Strata.Sample(AltitudeN, true, Runtime->StrataLut[i]);
		}
	}

	return Runtime;
}

void UCLVoxelWorldComponent::PublishToVoxelWorldManager()
{
	VOXEL_FUNCTION_COUNTER();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const AVoxelWorld* VoxelWorld = GetVoxelWorldOwner();
	if (!VoxelWorld)
	{
		return;
	}

	const TSharedRef<FCLVoxelWorldManager> Manager = FCLVoxelWorldManager::Get(World);
	Manager->SetWorldRuntime(*VoxelWorld, BuildWorldRuntime());
}

void UCLVoxelWorldComponent::OnRegister()
{
	Super::OnRegister();
	PublishToVoxelWorldManager();
}

void UCLVoxelWorldComponent::OnUnregister()
{
	if (UWorld* World = GetWorld())
	{
		const AVoxelWorld* VoxelWorld = GetVoxelWorldOwner();
		if (VoxelWorld)
		{
			const TSharedRef<FCLVoxelWorldManager> Manager = FCLVoxelWorldManager::Get(World);
			Manager->SetWorldRuntime(*VoxelWorld, nullptr);
		}
	}

	Super::OnUnregister();
}

#if WITH_EDITOR
void UCLVoxelWorldComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	PublishToVoxelWorldManager();
}
#endif