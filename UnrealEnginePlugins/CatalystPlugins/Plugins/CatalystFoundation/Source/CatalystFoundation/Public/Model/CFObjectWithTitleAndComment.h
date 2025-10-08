/**
 * @file CFObjectWithTitleAndComment.h
 * @brief Shared base for any data object that exposes a human-readable Title and Comment.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Model/CFAbstractObject.h"
#include "CFObjectWithTitleAndComment.generated.h"

USTRUCT(BlueprintType)
struct CATALYSTFOUNDATION_API FCFObjectWithTitleAndComment : public FCFAbstractObject
{
	GENERATED_BODY()

public:
	/** Human-readable display title (e.g., “Earth (Modern Temperate Mix)”). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF")
	FString Title;

	/** Optional descriptive comment or note. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CF", meta=(MultiLine=true))
	FString Comment;
};