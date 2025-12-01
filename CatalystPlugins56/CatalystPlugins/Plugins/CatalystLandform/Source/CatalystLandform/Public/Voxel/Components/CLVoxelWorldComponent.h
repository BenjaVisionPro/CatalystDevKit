#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Landform model & strata
#include "Model/CLModelAsset.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataAsset.h"
#include "Model/CLStrataCache.h"

// Landform runtime contracts
#include "Runtime/CLWorldGeneratorModel.h" // FCLWorldGeneratorModel, ECLCoordSpace

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

	/** Planet/world authoring model (SoT). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Catalyst|Landform")
	TSoftObjectPtr<UCLModelAsset> CLModelAsset;

	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	UCLModelAsset* GetModelAsset_NoLoad() const { return CLModelAsset.Get(); }

	// ------------------------------------------------------------------------
	// Planet band & addressing (authoring)
	// ------------------------------------------------------------------------

	/** Inner (base) radius in meters. R == altitude; base radius = InnerRadiusM. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform|Planet")
	double InnerRadiusM = 1000.0;

	/** World vertical thickness in meters: valid altitude [0 .. WorldHeightM]. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform|Planet", meta=(ClampMin="0.0"))
	double WorldHeightM = 2000.0;

	/** Coordinate mapping used by graphs (first: Geodesic). */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform|Planet")
	ECLCoordSpace CoordSpace = ECLCoordSpace::Geodesic;

	/** Normalized S wrap blend width (eg. 0.001). */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform|Planet", meta=(ClampMin="0.0", ClampMax="0.1"))
	double SeamBlendWidth = 0.001;

	/** Optional global seed for determinism (forwarded into world generator model). */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform|Planet")
	uint32 Seed = 0;

	// ------------------------------------------------------------------------
	// World/Voxel helpers
	// ------------------------------------------------------------------------

	/** Voxel size in centimeters (from AVoxelWorld). Min 1. */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 GetVoxelSize() const;

	/** Voxel size in meters (from AVoxelWorld). */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	double GetVoxelSizeM() const { return FMath::Max(1, GetVoxelSize()) / 100.0; }

	/** World height in meters (legacy pass-through from asset if set; falls back to property). */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	double GetWorldHeightM() const;

	/** Discrete sample count along Z: round(WorldHeightM / VoxelSizeM). Min 1. */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 GetResolution() const;

	/** Quantize AltitudeN [0..1] to height index [0..Resolution]. */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	int32 QuantizeAltitude(double AltitudeN) const;

	/** Planet center/location in world space (actor location). (Blueprint-friendly: FVector) */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	FVector GetPlanetCenterWS() const;

	/** Planet basis from actor rotation: East(+X), North(+Y), Up(+Z). (Blueprint-friendly: FVector) */
	UFUNCTION(BlueprintPure, Category="Catalyst|Landform")
	void GetPlanetBasis(FVector& OutEast, FVector& OutNorth, FVector& OutUp) const;

	/** Build an immutable world-generator model view for this voxel world (no UObjects). */
	TSharedRef<FCLWorldGeneratorModel> BuildWorldGeneratorModel() const;

	/**
	 * Push the current world-generator model into the voxel runtime subsystem (FVoxelCLSubsystem)
	 * and trigger an invalidation so graphs re-evaluate. Call this from your VPP runtime-init hook.
	 *
	 * NOTE: Implementation requires your project’s specific hook to access the runtime subsystems.
	 * This function is provided as the integration point.
	 */
	void PushWorldGeneratorModelToVoxelRuntime();

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
	static uint64 MakeCacheKey(const UCLStrataAsset* StrataAsset, int32 Resolution);
	const AVoxelWorld* GetVoxelWorldOwner() const;

private:
	/** Per (StrataAsset*, Resolution) bucket. Each bucket holds ONE vertical-column cache. */
	struct FPerResolutionCache
	{
		int32 Resolution = 0;
		FCLStrataCache Cache;
	};

	// Mutable: this is a lazy-populated cache used from const paths
	mutable FRWLock MapLock;
	mutable TMap<uint64, FPerResolutionCache> PerStrataPerRes;
};