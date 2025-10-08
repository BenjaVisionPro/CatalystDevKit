/**
 * @file CFValidatable.h
 * @brief Interface that models can implement to surface validation findings.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Validation/CFValidationTypes.h"
#include "CFValidatable.generated.h"

UINTERFACE(BlueprintType)
class CATALYSTFOUNDATION_API UCFValidatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Implement on UObjects (e.g., your UCFModelAsset subclass) to provide
 * structured validation messages. Thread-safe read access is the caller’s job.
 *
 * Contract:
 *  - Implementers should be fast and side-effect free (read-only).
 *  - Always fill Summary and Severity; Code/Path/Detail/FixHint are optional.
 */
class CATALYSTFOUNDATION_API ICFValidatable
{
	GENERATED_BODY()

public:
	/** Collect current validation findings. Implementers append into OutMessages. */
	virtual void CollectValidationMessages(TArray<FCFValidationMessage>& OutMessages) const = 0;
};