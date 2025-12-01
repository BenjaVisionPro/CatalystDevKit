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
			
		// HACK: expose Voxel private headers so we can see VoxelStampTree.h
        // because VoxelLayerBase.h (public) includes it.
        PrivateIncludePaths.Add(
            "/Users/jupiter/UnrealEngine/UE_5.6/Engine/Plugins/Marketplace/Voxel/Source/Voxel/Private"
        );
        
	}
}
