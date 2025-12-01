// ============================================================================
// Catalyst Landform — Planet Model Asset Factory (Editor)
// ----------------------------------------------------------------------------
// Purpose: Minimal factory to instantiate UCLPlanetModelAsset.
// Notes:
//   - Add(+) placement is handled entirely by UCLAssetDefinition_PlanetModel.
//   - Factory remains necessary so the engine can instantiate the asset type.
//   - No legacy AssetTools or custom menu handling.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CLPlanetModelAssetFactory.generated.h"

UCLASS()
class CATALYSTLANDFORMEDITOR_API UCLPlanetModelAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCLPlanetModelAssetFactory();

	// ----- UFactory -----
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;

	// Shown in some generic “New Asset” UIs if they ever list this factory
	virtual FString GetDefaultNewAssetName() const override
	{
		return TEXT("New Planet");
	}
};