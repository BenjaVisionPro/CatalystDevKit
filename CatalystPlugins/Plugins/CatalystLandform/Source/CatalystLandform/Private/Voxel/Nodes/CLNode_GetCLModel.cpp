#include "Voxel/Nodes/CLNode_GetCLModel.h"
#include "VoxelMinimal.h"

void FVoxelNode_GetCLModel::Compute(FVoxelGraphQuery Query) const
{
	if (!ModelAsset)
	{
		VOXEL_MESSAGE(Warning, "{0}: No ModelAsset set.", this);
		VoxelWorldRadiusMPin.Set(Query, 0.0);
		VoxelWorldHeightMPin.Set(Query, 0.0);
		return;
	}

	const FCLModel& Model = ModelAsset->GetModel();
	const double RadiusM = Model.VoxelWorldRadiusM;
	const double HeightM = Model.VoxelWorldHeightM;

	if (RadiusM <= 0.0 || HeightM <= 0.0 || HeightM >= RadiusM)
	{
		VOXEL_MESSAGE(Warning,
			"{0}: Invalid model values. RadiusM={1}, HeightM={2} (must be >0 and Height < Radius).",
			this, RadiusM, HeightM);

		VoxelWorldRadiusMPin.Set(Query, FMath::Max(0.0, RadiusM));
		VoxelWorldHeightMPin.Set(Query, FMath::Clamp(HeightM, 0.0, FMath::Max(0.0, RadiusM)));
		return;
	}

	VoxelWorldRadiusMPin.Set(Query, RadiusM);
	VoxelWorldHeightMPin.Set(Query, HeightM);
}