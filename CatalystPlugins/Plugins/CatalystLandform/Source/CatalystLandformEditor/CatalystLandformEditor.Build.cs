// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CatalystLandformEditor : ModuleRules
{
	public CatalystLandformEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		string EnginSourceFolder = EngineDirectory + "/Source/";
        PrivateIncludePaths.AddRange(
                new string[] {
                    EnginSourceFolder + "/Editor/DetailCustomizations/Private",
                });
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
        );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
        );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"AssetDefinition",
				// ... add other public dependencies that you statically link with here ...
			}
        );
	
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"EditorFramework",
				"UnrealEd",
				"PropertyEditor", 
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"CatalystFoundation",
				"CatalystFoundationEditor",
				"CatalystLandform",
			}
        );
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
        );
	}
}
