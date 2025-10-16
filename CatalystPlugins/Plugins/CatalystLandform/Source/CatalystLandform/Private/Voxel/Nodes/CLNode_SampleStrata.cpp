#include "Voxel/Nodes/CLNode_SampleStrata.h"

#include "Buffer/VoxelDoubleBuffers.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataAsset.h"
#include "Voxel/CLStratumSampleBuffer.h"

// -------------------------------------------------------------
// TODO: Wire these to your actual accessors.
// You said: CLModelAsset->Model.VoxelWorldHeightM  and  VoxelWorld->VoxelSize
// Replace the bodies below with those calls in your project.
// -------------------------------------------------------------
double FVoxelNode_SampleStrata::GetWorldHeight_FromNodeContext(const FVoxelGraphQuery& /*Query*/)
{
	// Example (replace with your actual lookup):
	// return CLModelAsset->Model.VoxelWorldHeightM;
	ensureMsgf(false, TEXT("Wire CLModelAsset->Model.VoxelWorldHeightM here."));
	return -1.0;
}

double FVoxelNode_SampleStrata::GetVoxelSize_FromNodeContext(const FVoxelGraphQuery& /*Query*/)
{
	// Example (replace with your actual lookup):
	// return Query.GetVoxelWorld()->VoxelSize;
	ensureMsgf(false, TEXT("Wire VoxelWorld->VoxelSize here."));
	return -1.0;
}

void FVoxelNode_SampleStrata::Compute(FVoxelGraphQuery Query) const
{
	const FVoxelDoubleBuffer& InAltN = *AltitudeNPin.Get(Query);
	const bool bDoNormalize          = NormalizePin.Get(Query).Get();

	if (!StrataAsset || StrataAsset->Strata.Strata.Num() == 0)
	{
		SamplesPin.Set(Query, FCLStratumSampleBuffer());
		return;
	}

	// Derive Resolution every call from world state
	const double WorldHeight = GetWorldHeight_FromNodeContext(Query);
	const double VoxelSize   = GetVoxelSize_FromNodeContext(Query);

	if (!(WorldHeight > 0.0 && VoxelSize > 0.0))
	{
		// Cannot compute resolution -> safe empty result
		SamplesPin.Set(Query, FCLStratumSampleBuffer());
		return;
	}

	const int32 Resolution = FMath::Max(1, static_cast<int32>(FMath::RoundHalfFromZero(WorldHeight / VoxelSize)));

	// Pass 1: gather shared arrays & count total outputs
	const int32 Count = InAltN.Num();
	TArray<TSharedPtr<const TArray<FCLStratumSample>>> SharedPerSample;
	SharedPerSample.SetNumUninitialized(Count);

	int32 Total = 0;
	for (int32 i = 0; i < Count; i++)
	{
		const int32 Hi = UCLStrataAsset::QuantizeHeight(InAltN[i], Resolution);
		const TSharedPtr<const TArray<FCLStratumSample>> Shared =
			StrataAsset->SampleStrataShared_Resolution(Resolution, Hi, bDoNormalize);

		SharedPerSample[i] = Shared;
		Total += Shared ? Shared->Num() : 0;
	}

	// Pass 2: allocate & copy
	FCLStratumSampleBuffer Out;
	Out.Allocate(Total);

	int32 WriteIndex = 0;
	for (int32 i = 0; i < Count; i++)
	{
		if (const auto& Shared = SharedPerSample[i])
		{
			for (const FCLStratumSample& S : *Shared)
			{
				Out.Set(WriteIndex++, S);
			}
		}
	}

	checkSlow(WriteIndex == Total);
	SamplesPin.Set(Query, Out);
}