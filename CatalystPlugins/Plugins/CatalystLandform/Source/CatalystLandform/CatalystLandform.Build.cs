// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

using UnrealBuildTool;

public class CatalystLandform : ModuleRules
{
	public CatalystLandform(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {

			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {

			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Json",
                "JsonUtilities",
                "Voxel",
                "VoxelCore",
                "VoxelGraph",
                "CatalystFoundation",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
			
		// VoxelLayerBase.h includes VoxelStampTree.h from the Voxel module's private headers.
		PrivateIncludePaths.Add(System.IO.Path.Combine(GetModuleDirectory("Voxel"), "Private"));
	}
}
