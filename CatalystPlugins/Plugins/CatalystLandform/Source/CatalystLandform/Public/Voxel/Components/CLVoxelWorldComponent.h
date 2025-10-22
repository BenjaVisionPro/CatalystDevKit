#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Model/CLModelAsset.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataAsset.h"
#include "Model/CLStrataCache.h"
#include "CLVoxelWorldComponent.generated.h"

class AVoxelWorld;

/**
 * Add this to a Voxel World to make it Landform-driven.
 * Dev doc: “Add CLVoxelWorldComponent to your AVoxelWorld and set CLModelAsset.”
 */
UCLASS(ClassGroup=(Catalyst), meta=(BlueprintSpawnableComponent))
class CATALYSTLANDFORM_API UCLVoxelWorldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCLVoxelWorldComponent();

	/** Configuration (SoT). Contains CLModel with VoxelWorldHeightM and references to CL sub-assets. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Catalyst|Landform")
	TSoftObjectPtr<UCLModelAsset> CLModelAsset;

	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	UCLModelAsset* GetModelAsset_NoLoad() const { return CLModelAsset.Get(); }

	// World/Voxel helpers
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 GetVoxelSize() const;

	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	double GetWorldHeightM() const;

	/** Discrete sample count along Z: round(WorldHeightM / (VoxelSizeCm/100)). Min 1. */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 GetResolution() const;

	/** Quantize AltitudeN [0..1] to height index [0..Resolution]. */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 QuantizeAltitude(double AltitudeN) const;

	/** Shared immutable samples for (StrataAsset, HeightIndex). */
	TSharedPtr<const TArray<FCLStratumSample>> GetSharedStrataSamples(
		const UCLStrataAsset* StrataAsset,
		int32 HeightIndex,
		bool bNormalize) const;

	/** Flush everything (model change or VoxelSize change). */
	UFUNCTION(BlueprintCallable, Category="Catalyst|Landform")
	void InvalidateCaches();

protected:
	//~ UActorComponent
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	/** Per (StrataAsset*, Resolution) bucket. Each bucket holds ONE vertical-column cache. */
	struct FPerResolutionCache
	{
		int32 Resolution = 0;
		FCLStrataCache Cache;
	};

	static uint64 MakeCacheKey(const UCLStrataAsset* StrataAsset, int32 Resolution);

	// Mutable: this is a lazy-populated cache used from const paths
	mutable FRWLock MapLock;
	mutable TMap<uint64, FPerResolutionCache> PerStrataPerRes;

	const AVoxelWorld* GetVoxelWorldOwner() const;
};