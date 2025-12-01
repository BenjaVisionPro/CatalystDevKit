// Copyright © Catalyst
#pragma once

#include "CoreMinimal.h"
#include "VoxelSubsystem.h"
#include "Runtime/CLWorldGeneratorModel.h"
#include "VoxelCLSubsystem.generated.h"

// Runtime model provider for CL. No dependency tracker here (2.0p8 pattern differs).
USTRUCT()
struct CATALYSTLANDFORM_API FVoxelCLSubsystem : public FVoxelSubsystem
{
	GENERATED_BODY()
	GENERATED_VOXEL_SUBSYSTEM_BODY()

public:
	// Live model (thread-safe reads guarded by our lock)
	const FCLWorldGeneratorModel* GetModelOrNull() const
	{
		FReadScopeLock _(Lock);
		return Model.IsSet() ? &Model.GetValue() : nullptr;
	}

	void SetModel(const FCLWorldGeneratorModel& InModel)
	{
		FWriteScopeLock _(Lock);
		Model = InModel;
	}

	// Defaults when no model present (optional)
	ECLCoordSpace DefaultCoordSpace = ECLCoordSpace::Geodesic;

private:
	mutable FRWLock Lock;
	TOptional<FCLWorldGeneratorModel> Model;
};