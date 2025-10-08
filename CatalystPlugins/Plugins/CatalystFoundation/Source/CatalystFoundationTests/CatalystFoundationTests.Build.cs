using UnrealBuildTool;

public class CatalystFoundationTests : ModuleRules
{
    public CatalystFoundationTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Type = ModuleType.CPlusPlus;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystFoundation"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystFoundation"
        });
    }
}
