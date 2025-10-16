#pragma once

#include "CoreMinimal.h"

// Must come before specialization
#include "VoxelPinType.h"
// Base class + GENERATED_VOXEL_BUFFER_STRUCT_BODY macro
#include "VoxelBufferStruct.h"

#include "Model/CLStrata.h" // FCLStratumSample

// Forward declare WITHOUT USTRUCT()
struct CATALYSTLANDFORM_API FCLStratumSampleBuffer;

// Map uniform struct -> buffer type for VPP pins
template<> struct TVoxelBufferTypeImpl<FCLStratumSample>
{
	using Type = FCLStratumSampleBuffer;
};

#include "CLStratumSampleBuffer.generated.h"

USTRUCT()
struct CATALYSTLANDFORM_API FCLStratumSampleBuffer final : public FVoxelBufferStruct
{
	GENERATED_BODY()
	GENERATED_VOXEL_BUFFER_STRUCT_BODY(FCLStratumSampleBuffer, FCLStratumSample);

private:
	TArray<FCLStratumSample> Data;

public:
	FORCEINLINE void Allocate(const int32 Count)
	{
		Data.SetNumUninitialized(Count);
	}

	FORCEINLINE int32 Num() const
	{
		return Data.Num();
	}

	// Return const value (not reference)
	FORCEINLINE const FCLStratumSample operator[](const int32 Index) const
	{
		check(static_cast<uint32>(Index) < static_cast<uint32>(Data.Num()));
		return Data[Index];
	}

	FORCEINLINE void Set(const int32 Index, const FCLStratumSample& Value)
	{
		check(static_cast<uint32>(Index) < static_cast<uint32>(Data.Num()));
		Data[Index] = Value;
	}
};