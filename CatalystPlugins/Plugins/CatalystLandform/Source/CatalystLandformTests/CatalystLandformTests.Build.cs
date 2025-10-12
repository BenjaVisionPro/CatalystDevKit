using UnrealBuildTool;

public class CatalystLandformTests : ModuleRules
{
    public CatalystLandformTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Type = ModuleType.CPlusPlus;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystLandform"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystLandform"
        });
    }
}
