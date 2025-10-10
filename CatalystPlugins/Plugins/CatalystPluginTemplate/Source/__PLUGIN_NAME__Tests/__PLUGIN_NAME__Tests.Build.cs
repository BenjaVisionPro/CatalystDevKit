using UnrealBuildTool;

public class __PLUGIN_NAME__Tests : ModuleRules
{
    public __PLUGIN_NAME__Tests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Type = ModuleType.CPlusPlus;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "__PLUGIN_NAME__"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "__PLUGIN_NAME__"
        });
    }
}
