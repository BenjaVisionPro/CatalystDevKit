// ============================================================================
// Catalyst Ecosystem — Model Asset Factory (Editor)
// ----------------------------------------------------------------------------
// Purpose: Minimal factory to instantiate U__PREFIX__ModelAsset.
// Notes:
//   - Add(+) placement is handled entirely by U__PREFIX__AssetDefinition_Model.
//   - Factory remains necessary so the engine can instantiate the asset type.
//   - No legacy AssetTools or custom menu handling.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "__PREFIX__ModelAssetFactory.generated.h"

class U__PREFIX__ModelAsset;

UCLASS()
class CATALYSTECOSYSTEMEDITOR_API U__PREFIX__ModelAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	U__PREFIX__ModelAssetFactory();

	// ----- UFactory -----
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
	
	virtual FString GetDefaultNewAssetName() const override { return TEXT("New Ecosystem"); }
};