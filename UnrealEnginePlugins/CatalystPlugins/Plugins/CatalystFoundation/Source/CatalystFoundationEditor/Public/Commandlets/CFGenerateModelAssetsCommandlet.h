// ============================================
// Catalyst Foundation — Generate Model Assets (Commandlet)
// ============================================
#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "CFGenerateModelAssetsCommandlet.generated.h"

/**
 * Generate model assets from JSON files.
 *
 * Usage (examples):
 *   UnrealEditor-Cmd -run=CFGenerateModelAssets
 *       -Plugin=CatalystEcosystem
 *       -AssetClass=/Script/CatalystEcosystem.CEModelAsset
 *       [-InputDir=Model] [-Overwrite] [-DryRun] [-FailFast]
 *
 * Output:
 *   - Creates/updates assets under /<Plugin>/Model/
 *   - Writes a CI report to Saved/<Plugin>/Reports/CF_GenerateReport_<UTC>.json
 */
UCLASS()
class CATALYSTFOUNDATIONEDITOR_API UCFGenerateModelAssetsCommandlet : public UCommandlet
{
	GENERATED_BODY()
public:
	UCFGenerateModelAssetsCommandlet();

	// UCommandlet
	virtual int32 Main(const FString& Params) override;
};
