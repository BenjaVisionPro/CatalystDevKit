#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"

#include "Model/CLWorld.h"
#include "Model/CLStrataAsset.h"

#include "CLWorldAsset.generated.h"

/**
 * CLWorld asset: drives ONE VoxelWorld.
 * References shared Strata asset.
 */
UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLWorldAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|World")
	FCLWorld World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|World")
	TSoftObjectPtr<UCLStrataAsset> StrataAsset;

	virtual FString GetSummaryText() const override
	{
		return TEXT("World (outer radius + shell height) + shared strata.");
	}

	const FCLWorld& GetWorld() const { return World; }
	FCLWorld&       GetWorld()       { return World; }

protected:
	virtual FString GetPluginNameForPaths() const override { return TEXT("CatalystLandform"); }
	virtual int32   GetSchemaVersion() const override { return 1; }

	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCLWorld::StaticStruct(); }
	virtual void*          GetPayloadMemory() override { return &World; }
	virtual const void*    GetPayloadMemory() const override { return &World; }

	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};