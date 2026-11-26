#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Model/CLWorldAsset.h"
#include "Voxel/Components/CLVoxelWorldComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LandformTests_SetGetString,
    "CL.Landform.SetGetString",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool LandformTests_SetGetString::RunTest(const FString& Parameters)
{
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCLWorldAssetRuntimeTest,
    "CL.Landform.WorldAssetRuntime",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCLWorldAssetRuntimeTest::RunTest(const FString&)
{
    auto* Asset = NewObject<UCLWorldAsset>();
    Asset->GetWorldDefinition().OuterRadiusM = 3000.0;
    Asset->GetWorldDefinition().WorldHeightM = 800.0;

    auto* Component = NewObject<UCLVoxelWorldComponent>();
    Component->CLWorldAsset = Asset;
    const auto Runtime = Component->BuildWorldRuntime();
    if (!TestTrue(TEXT("The world asset supplies a runtime snapshot"), Runtime.IsValid()))
    {
        return false;
    }

    TestEqual(TEXT("The inner radius comes from the world definition"), Runtime->InnerRadiusM, 2200.0);
    TestEqual(TEXT("The height comes from the world definition"), Runtime->WorldHeightM, 800.0);
    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
