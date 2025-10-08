/**
 * @file CFValidationTypes.h
 * @brief Lightweight, shared validation primitives for Catalyst models.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */
#pragma once

#include "CoreMinimal.h"
#include "CFValidationTypes.generated.h"

/** Severity levels used across runtime/editor. */
UENUM(BlueprintType)
enum class ECFValidationSeverity : uint8
{
	Info     UMETA(DisplayName="Info"),
	Warning  UMETA(DisplayName="Warning"),
	Error    UMETA(DisplayName="Error")
};

/**
 * @brief A single validation finding.
 * Keep this stable—editor widgets and CI tooling depend on it.
 */
USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFValidationMessage
{
	GENERATED_BODY()

	/** Error/Warning/Info. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	ECFValidationSeverity Severity = ECFValidationSeverity::Info;

	/** Short, human-readable summary (“Biome has no name”). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	FText Summary;

	/** Optional longer explanation / diagnostic context. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	FText Detail;

	/** Optional machine-friendly code (“Biome.MissingName”) for CI grepping. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	FName Code;

	/** Optional logical path to the offending item (“/Ecosystems/0/Biomes[2]”). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	FString Path;

	/** Optional “fix-it” hint shown in editor UIs. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CF|Validation")
	FText FixHint;

	FCFValidationMessage() = default;

	static FCFValidationMessage Make(ECFValidationSeverity InSeverity, FName InCode, FText InSummary,
		FText InDetail = FText(), FString InPath = FString(), FText InFix = FText())
	{
		FCFValidationMessage M;
		M.Severity = InSeverity;
		M.Code     = InCode;
		M.Summary  = MoveTemp(InSummary);
		M.Detail   = MoveTemp(InDetail);
		M.Path     = MoveTemp(InPath);
		M.FixHint  = MoveTemp(InFix);
		return M;
	}
};