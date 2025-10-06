// ============================================================================
// Catalyst Ecosystem — Model Asset Factory (Editor)
// ----------------------------------------------------------------------------
// Purpose: Minimal factory to instantiate UCEModelAsset.
// Notes:
//   - Add(+) placement is handled entirely by UCEAssetDefinition_Model.
//   - Factory remains necessary so the engine can instantiate the asset type.
//   - No legacy AssetTools or custom menu handling.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CEModelAssetFactory.generated.h"

class UCEModelAsset;

UCLASS()
class CATALYSTECOSYSTEMEDITOR_API UCEModelAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCEModelAssetFactory();

	// ----- UFactory -----
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
};