#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"
#include "Model/CLStrata.h"
#include "CLStrataAsset.generated.h"

UCLASS(BlueprintType)
class CATALYSTLANDFORM_API UCLStrataAsset : public UCFModelAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Landform|Strata")
	FCLStrata Strata;

	virtual FString GetSummaryText() const override
	{
		return FString::Printf(TEXT("Strata: %d"), Strata.Strata.Num());
	}

	const FCLStrata& GetStrata() const { return Strata; }
	FCLStrata&       GetStrata()       { return Strata; }

	// Pure helper: copy results out (no caching here)
	void SampleStrata(double AltitudeN, bool bNormalize, TArray<FCLStratumSample>& Out) const
	{
		Strata.Sample(AltitudeN, bNormalize, Out);
	}

protected:
	virtual FString        GetPluginNameForPaths() const override { return TEXT("CatalystLandform"); }
	virtual int32          GetSchemaVersion() const override { return 1; }
	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCLStrata::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Strata; }
	virtual const void*    GetPayloadMemory()       const override { return &Strata; }

	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;
};