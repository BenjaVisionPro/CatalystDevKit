// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CatalystPlugins : ModuleRules
{
	public CatalystPlugins(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CatalystPlugins",
			"CatalystPlugins/Variant_Platforming",
			"CatalystPlugins/Variant_Platforming/Animation",
			"CatalystPlugins/Variant_Combat",
			"CatalystPlugins/Variant_Combat/AI",
			"CatalystPlugins/Variant_Combat/Animation",
			"CatalystPlugins/Variant_Combat/Gameplay",
			"CatalystPlugins/Variant_Combat/Interfaces",
			"CatalystPlugins/Variant_Combat/UI",
			"CatalystPlugins/Variant_SideScrolling",
			"CatalystPlugins/Variant_SideScrolling/AI",
			"CatalystPlugins/Variant_SideScrolling/Gameplay",
			"CatalystPlugins/Variant_SideScrolling/Interfaces",
			"CatalystPlugins/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
