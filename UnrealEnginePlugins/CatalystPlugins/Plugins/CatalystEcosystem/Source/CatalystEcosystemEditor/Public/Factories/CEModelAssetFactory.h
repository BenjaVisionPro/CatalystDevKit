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

	// ---- UFactory ----
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
};