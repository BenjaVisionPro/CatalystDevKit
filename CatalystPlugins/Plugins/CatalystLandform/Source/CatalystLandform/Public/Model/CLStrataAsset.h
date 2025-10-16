#pragma once

#include "CoreMinimal.h"
#include "Model/CFModelAsset.h"
#include "Model/CLStrata.h"
#include "Model/CLStrataCache.h"
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

	// Helper
	static int32 QuantizeHeight(double AltitudeN, int32 Resolution)
	{
		return FCLStrataCache::QuantizeHeight(AltitudeN, Resolution);
	}

	// Resolution is passed per-call. Cache stores it only to invalidate when changed.
	TSharedPtr<const TArray<FCLStratumSample>> SampleStrataShared_Resolution(
		int32 Resolution,
		int32 HeightIndex,
		bool bNormalize) const;

protected:
	virtual FString        GetPluginNameForPaths() const override { return TEXT("CatalystLandform"); }
	virtual int32          GetSchemaVersion() const override { return 1; }
	virtual UScriptStruct* GetPayloadScriptStruct() const override { return FCLStrata::StaticStruct(); }
	virtual void*          GetPayloadMemory()             override { return &Strata; }
	virtual const void*    GetPayloadMemory()       const override { return &Strata; }

	virtual void NormalizePayload() override;
	virtual bool ValidatePayload(FString& OutError) const override;
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const override;

private:
	mutable FCLStrataCache Cache;
};