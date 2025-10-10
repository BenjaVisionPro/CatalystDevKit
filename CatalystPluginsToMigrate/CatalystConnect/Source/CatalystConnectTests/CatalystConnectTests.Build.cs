using UnrealBuildTool;

public class CatalystConnectTests : ModuleRules
{
    public CatalystConnectTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Type = ModuleType.CPlusPlus;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystConnect"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystConnect"
        });
    }
}
