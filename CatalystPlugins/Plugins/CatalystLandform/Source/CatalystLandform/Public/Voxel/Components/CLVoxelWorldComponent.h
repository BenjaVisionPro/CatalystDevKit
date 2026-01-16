#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Model/CLPlanetModelAsset.h" // TODO: rename to CLWorld asset
#include "Model/CLStrataAsset.h"

#include "Voxel/Runtime/CLEnums.h"
#include "Voxel/Runtime/CLWorldRuntime.h"

#include "CLVoxelWorldComponent.generated.h"

class AVoxelWorld;

/**
 * Attach to an AVoxelWorld actor to provide Catalyst Landform world data.
 *
 * Responsibilities:
 *  - Hold editor-selected CLWorld and Strata assets
 *  - Build a runtime-safe FCLWorldRuntime snapshot (no UObjects)
 *  - Publish that snapshot to FCLVoxelWorldManager for this UWorld
 */
UCLASS(ClassGroup=(Catalyst), meta=(BlueprintSpawnableComponent))
class CATALYSTLANDFORM_API UCLVoxelWorldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCLVoxelWorldComponent();

	// --- Authoring assets ---

	/** World configuration asset (currently named PlanetModel in scaffold). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Catalyst|Landform")
	TSoftObjectPtr<UCLPlanetModelAsset> CLWorldAsset;

	/** Shared strata asset used by this world. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Catalyst|Landform")
	TSoftObjectPtr<UCLStrataAsset> StrataAsset;

	// --- Determinism / graph-space ---

	/** Coordinate mapping used by graphs. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform")
	ECLCoordSpace CoordSpace = ECLCoordSpace::Geodesic;

	/** Normalized seam blend width near coordinate seam. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform", meta=(ClampMin="0.0", ClampMax="0.1"))
	double SeamBlendWidthN = 0.001;

	/** Optional global seed for determinism. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform")
	uint32 Seed = 0;

	/** Strata lookup resolution. LUT size will be (Resolution + 1). 0 disables precompute. */
	UPROPERTY(EditAnywhere, Category="Catalyst|Landform", meta=(ClampMin="0"))
	int32 StrataLutResolution = 2048;

public:
	/** Build a runtime-safe snapshot from the current component settings. */
	TSharedPtr<const FCLWorldRuntime> BuildWorldRuntime() const;

	/** Publish current snapshot to the per-UWorld manager and invalidate dependents. */
	void PublishToVoxelWorldManager();

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	const AVoxelWorld* GetVoxelWorldOwner() const;
};