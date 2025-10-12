// ============================================================================
// Catalyst Landform — Model Asset Factory (Editor)
// ----------------------------------------------------------------------------
// Purpose: Minimal factory to instantiate UCLModelAsset.
// Notes:
//   - Add(+) placement is handled entirely by UCLAssetDefinition_Model.
//   - Factory remains necessary so the engine can instantiate the asset type.
//   - No legacy AssetTools or custom menu handling.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CLModelAssetFactory.generated.h"

class UCLModelAsset;

UCLASS()
class CATALYSTLANDFORMEDITOR_API UCLModelAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UCLModelAssetFactory();

	// ----- UFactory -----
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
	
	virtual FString GetDefaultNewAssetName() const override { return TEXT("New Landform"); }
};