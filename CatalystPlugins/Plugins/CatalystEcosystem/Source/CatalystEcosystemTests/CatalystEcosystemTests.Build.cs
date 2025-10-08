using UnrealBuildTool;

public class CatalystEcosystemTests : ModuleRules
{
    public CatalystEcosystemTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Type = ModuleType.CPlusPlus;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystEcosystem"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "CatalystEcosystem"
        });
    }
}
