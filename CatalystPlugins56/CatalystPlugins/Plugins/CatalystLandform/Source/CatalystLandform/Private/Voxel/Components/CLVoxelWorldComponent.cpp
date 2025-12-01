#include "Voxel/Components/CLVoxelWorldComponent.h"

#include "VoxelWorld.h"               // VPP world class
#include "GameFramework/Actor.h"
#include "Engine/World.h"

UCLVoxelWorldComponent::UCLVoxelWorldComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

const AVoxelWorld* UCLVoxelWorldComponent::GetVoxelWorldOwner() const
{
	return Cast<AVoxelWorld>(GetOwner());
}

int32 UCLVoxelWorldComponent::GetVoxelSize() const
{
	if (const AVoxelWorld* World = GetVoxelWorldOwner())
	{
		return FMath::Max(1, World->VoxelSize); // centimeters
	}
	return 1;
}

double UCLVoxelWorldComponent::GetWorldHeightM() const
{
	if (const UCLModelAsset* Asset = GetModelAsset_NoLoad())
	{
		return Asset->Model.VoxelWorldHeightM;
	}
	return WorldHeightM;
}

int32 UCLVoxelWorldComponent::GetResolution() const
{
	const double HeightM = GetWorldHeightM();
	const int32  VoxelCm = GetVoxelSize();

	if (HeightM <= 0.0 || VoxelCm <= 0)
	{
		return 1;
	}

	const double VoxelSizeM = double(VoxelCm) / 100.0;
	return FMath::Max(1, FMath::RoundToInt(HeightM / VoxelSizeM));
}

int32 UCLVoxelWorldComponent::QuantizeAltitude(const double AltitudeN) const
{
	const int32 Res = GetResolution();
	const double X  = FMath::Clamp(AltitudeN, 0.0, 1.0);
	return FMath::Clamp(FMath::RoundToInt(X * Res), 0, Res);
}

FVector UCLVoxelWorldComponent::GetPlanetCenterWS() const
{
	const AActor* Owner = GetOwner();
	return Owner ? Owner->GetActorLocation() : FVector::ZeroVector;
}

void UCLVoxelWorldComponent::GetPlanetBasis(FVector& OutEast, FVector& OutNorth, FVector& OutUp) const
{
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		OutEast  = FVector::ForwardVector;
		OutNorth = FVector::RightVector;
		OutUp    = FVector::UpVector;
		return;
	}

	const FQuat Rot = Owner->GetActorQuat();
	OutEast  = Rot.GetAxisX(); // +X
	OutNorth = Rot.GetAxisY(); // +Y
	OutUp    = Rot.GetAxisZ(); // +Z
}

TSharedRef<FCLWorldGeneratorModel> UCLVoxelWorldComponent::BuildWorldGeneratorModel() const
{
	TSharedRef<FCLWorldGeneratorModel> Model = MakeShared<FCLWorldGeneratorModel>();
	Model->InnerRadiusM   = InnerRadiusM;
	Model->WorldHeightM   = GetWorldHeightM();
	Model->CoordSpace     = CoordSpace;
	Model->SeamBlendWidth = SeamBlendWidth;
	Model->Seed           = Seed;
	return Model;
}

void UCLVoxelWorldComponent::PushWorldGeneratorModelToVoxelRuntime()
{
	// Integration hook: set FVoxelCLSubsystem::Model and invalidate VPP runtime as needed.
	// Left intentionally empty until your runtime wiring is added in your VPP init path.
}

uint64 UCLVoxelWorldComponent::MakeCacheKey(const UCLStrataAsset* StrataAsset, const int32 Resolution)
{
	const uint64 A = (uint64)(UPTRINT)StrataAsset;
	const uint64 B = (uint64)Resolution;
	return (A << 17) ^ (B * 0x9E3779B97F4A7C15ull);
}

TSharedPtr<const TArray<FCLStratumSample>> UCLVoxelWorldComponent::GetSharedStrataSamples(
	const UCLStrataAsset* StrataAsset,
	const int32 HeightIndex,
	const bool bNormalize) const
{
	if (!StrataAsset)
	{
		return nullptr;
	}

	const int32 Resolution = GetResolution();
	const uint64 Key = MakeCacheKey(StrataAsset, Resolution);

	// Fast read
	{
		FReadScopeLock _R(MapLock);
		if (const FPerResolutionCache* Found = PerStrataPerRes.Find(Key))
		{
			return Found->Cache.GetOrBuild(StrataAsset->Strata, HeightIndex, bNormalize, Resolution);
		}
	}

	// Miss -> write
	FWriteScopeLock _W(MapLock);
	FPerResolutionCache& Entry = PerStrataPerRes.FindOrAdd(Key);
	if (Entry.Resolution != Resolution)
	{
		Entry.Resolution = Resolution;
		Entry.Cache.Invalidate();
	}
	return Entry.Cache.GetOrBuild(StrataAsset->Strata, HeightIndex, bNormalize, Resolution);
}

void UCLVoxelWorldComponent::InvalidateCaches()
{
	FWriteScopeLock _W(MapLock);
	PerStrataPerRes.Reset();
}

void UCLVoxelWorldComponent::OnRegister()
{
	Super::OnRegister();
}

void UCLVoxelWorldComponent::OnUnregister()
{
	InvalidateCaches();
	Super::OnUnregister();
}

#if WITH_EDITOR
void UCLVoxelWorldComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	InvalidateCaches();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif