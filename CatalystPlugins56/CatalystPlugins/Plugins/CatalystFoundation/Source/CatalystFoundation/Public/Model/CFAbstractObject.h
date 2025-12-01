/**
 * @file CFAbstractObject.h
 * @brief Abstract base type used as a shared foundation for Catalyst data objects.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "CFAbstractObject.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFAbstractObject
{
	GENERATED_BODY()

public:
	FCFAbstractObject()
		: Id(FGuid()) // or FGuid::NewGuid() if you prefer runtime-unique defaults
	{
	}

	explicit FCFAbstractObject(const FGuid& InId)
		: Id(InId)
	{
	}

	FCFAbstractObject(const FCFAbstractObject&) = default;
	FCFAbstractObject(FCFAbstractObject&&) = default;
	FCFAbstractObject& operator=(const FCFAbstractObject&) = default;
	FCFAbstractObject& operator=(FCFAbstractObject&&) = default;

public:
	/** Stable identifier for cross-references and lookups. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF")
	FGuid Id;
};