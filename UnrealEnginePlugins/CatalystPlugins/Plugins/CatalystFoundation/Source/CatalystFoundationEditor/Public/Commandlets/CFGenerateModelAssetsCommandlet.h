// ============================================
// Catalyst Foundation — Generate Model Assets (public)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "CFGenerateModelAssetsCommandlet.generated.h"

/**
 * Generate model assets from JSON files.
 *
 * Scans <PluginRoot>/<InputDir> for *.json and (re)generates assets at
 * /<Plugin>/Model/<Stem>.uasset where <Stem> is the JSON filename (no extension).
 *
 * Usage:
 *   UnrealEditor-Cmd -run=CFGenerateModelAssets
 *       -Plugin=<PluginName>
 *       -AssetClass=/Script/<Module>.<YourModelAssetClass>
 *       [-InputDir=Model] [-Overwrite] [-DryRun]
 *
 * Notes:
 *   - AssetClass must derive from UCFModelAsset (it provides ApplyJsonString).
 *   - Use -Overwrite to update existing uassets; otherwise they are skipped.
 *   - Use -DryRun to log what would happen without saving.
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