#include "Voxel/Nodes/CLNode_SampleStrata.h"

#include "Model/CLStrata.h"
#include "Model/CLStrataCache.h"

// Buffers
#include "Buffer/VoxelIntegerBuffers.h"
#include "Buffer/VoxelDoubleBuffers.h"
#include "Buffer/VoxelNameBuffer.h"

void FVoxelNode_SampleStrata::Compute(const FVoxelGraphQuery Query) const
{
	// Read inputs
	const FVoxelDoubleBuffer& InAltN  = *AltitudeNPin.Get(Query);
	const bool bDoNormalize           = NormalizePin.Get(Query).Get();
	const int32 Resolution            = ResolutionPin.Get(Query).Get();

	// Prepare outputs
	const TSharedRef<FVoxelInt32Buffer>  OutIndex  = MakeShared<FVoxelInt32Buffer>();
	const TSharedRef<FVoxelDoubleBuffer> OutWeight = MakeShared<FVoxelDoubleBuffer>();
	const TSharedRef<FVoxelNameBuffer>   OutTitle  = MakeShared<FVoxelNameBuffer>();

	// Guards
	if (!StrataAsset || StrataAsset->Strata.Strata.Num() == 0 || Resolution <= 0)
	{
		StratumIndexPin.Set(Query,  OutIndex);
		StratumWeightNPin.Set(Query, OutWeight);
		StratumTitlePin.Set(Query,  OutTitle);
		return;
	}

	// Use the cache helper you already have
	auto QuantizeHeight = [Resolution](double AltN) -> int32
	{
		return FCLStrataCache::QuantizeHeight(AltN, Resolution);
	};

	// Resolve GUID -> index in the asset
	auto ResolveIndexFromGuid = [Asset = StrataAsset](const FGuid& Id) -> int32
	{
		const TArray<FCLStratum>& Arr = Asset->Strata.Strata;
		for (int32 i = 0; i < Arr.Num(); i++)
		{
			if (Arr[i].Id == Id)
			{
				return i;
			}
		}
		return INDEX_NONE;
	};

	// Pass 1: count entries
	int32 Total = 0;
	{
		const int32 Count = InAltN.Num();
		for (int32 i = 0; i < Count; i++)
		{
			const int32 H = QuantizeHeight(InAltN[i]);

			// No singleton: use a local cache instance per evaluation
			FCLStrataCache Cache;
			if (TSharedPtr<const TArray<FCLStratumSample>> S =
					Cache.GetOrBuild(StrataAsset->Strata, H, bDoNormalize, Resolution))
			{
				Total += S->Num();
			}
		}
	}

	OutIndex->Allocate(Total);
	OutWeight->Allocate(Total);
	OutTitle->Allocate(Total);

	// Pass 2: fill
	int32 WriteIndex = 0;
	{
		const int32 Count = InAltN.Num();
		for (int32 i = 0; i < Count; i++)
		{
			const int32 H = QuantizeHeight(InAltN[i]);

			FCLStrataCache Cache;
			if (TSharedPtr<const TArray<FCLStratumSample>> S =
					Cache.GetOrBuild(StrataAsset->Strata, H, bDoNormalize, Resolution))
			{
				for (const FCLStratumSample& Sample : *S)
				{
					const int32 Index = ResolveIndexFromGuid(Sample.StratumId);
					if (!StrataAsset->Strata.Strata.IsValidIndex(Index))
					{
						continue;
					}

					OutIndex->Set(WriteIndex,  Index);
					OutWeight->Set(WriteIndex, Sample.WeightN);

					const FName TitleName(*StrataAsset->Strata.Strata[Index].Title);
					OutTitle->Set(WriteIndex, TitleName);

					++WriteIndex;
				}
			}
		}
	}

	checkSlow(WriteIndex == Total);

	// Push outputs (buffer pins expect shared refs)
	StratumIndexPin.Set(Query,  OutIndex);
	StratumWeightNPin.Set(Query, OutWeight);
	StratumTitlePin.Set(Query,  OutTitle);
}