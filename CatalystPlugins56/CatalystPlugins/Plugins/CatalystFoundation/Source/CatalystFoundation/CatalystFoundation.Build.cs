// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

using UnrealBuildTool;

public class CatalystFoundation : ModuleRules
{
	public CatalystFoundation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		
		// ==============================================================
        // CATALYST_LOG — compile-time toggle for logging system
        // --------------------------------------------------------------
        // This definition controls whether logging code (CF_LOG, CF_INFO, etc.)
        // is compiled into the build. It lets you strip out *all* logging 
        // for optimized shipping builds without changing any source files.
        //
        // When CATALYST_LOG == 1:
        //   - Logging macros expand to UE_LOG() calls with full context output.
        //
        // When CATALYST_LOG == 0:
        //   - Logging macros compile to empty stubs (no overhead, no strings).
        // ==============================================================
        
        if (Target.Configuration == UnrealTargetConfiguration.Shipping)
        {
            // Disable logging in shipping builds for maximum performance.
            PublicDefinitions.Add("CATALYST_LOG=0");
        }
        else
        {
            // Enable logging in all non-shipping builds (Debug, Development, Test).
            PublicDefinitions.Add("CATALYST_LOG=1");
        }
		
		
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
                "AssetRegistry",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Projects",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}