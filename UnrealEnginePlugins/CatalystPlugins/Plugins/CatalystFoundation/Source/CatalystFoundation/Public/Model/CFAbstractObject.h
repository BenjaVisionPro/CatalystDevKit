/**
 * @file CFAbstractObject.h
 * @brief Abstract base type used as a shared foundation for Catalyst data objects.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

// Public/Model/CFAbstractObject.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "CFAbstractObject.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFAbstractObject
{
	GENERATED_BODY()

public:
	// Always initialize UPROPERTY members in ctors
	FCFAbstractObject()
		: Id(FGuid())              // or FGuid::NewGuid() if you want a runtime-unique default
		, Name(TEXT(""))           // example if you have more fields
		, Version(1)               // example
	{
	}

	// If you have other ctors, init everything there, too.
	explicit FCFAbstractObject(const FGuid& InId)
		: Id(InId)
		, Name(TEXT(""))
		, Version(1)
	{
	}

	// Copy/move must keep a valid value as well (defaults are fine)
	FCFAbstractObject(const FCFAbstractObject&) = default;
	FCFAbstractObject(FCFAbstractObject&&) = default;
	FCFAbstractObject& operator=(const FCFAbstractObject&) = default;
	FCFAbstractObject& operator=(FCFAbstractObject&&) = default;

public:
	/** Example fields — ensure you initialize whatever you actually have */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF")
	FGuid Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF")
	int32 Version = 1;
};