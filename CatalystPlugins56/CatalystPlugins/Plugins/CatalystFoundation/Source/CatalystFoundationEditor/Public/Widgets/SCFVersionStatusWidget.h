/**
 * @file SCFVersionStatusWidget.h
 * @brief Compact banner summarizing Schema / Plugin / Engine version status for a model asset.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UCFModelAsset;
class STextBlock;

/**
 * @brief Displays Schema, Plugin, and Engine version info for a given model asset.
 *        No background polling — call SetAsset() or Refresh() manually when needed.
 */
class CATALYSTFOUNDATIONEDITOR_API SCFVersionStatusWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCFVersionStatusWidget) {}
	SLATE_END_ARGS()

	/** Construct the widget, optionally bound to an asset. */
	void Construct(const FArguments& InArgs, UCFModelAsset* InAsset);

	/** Replace the asset and manually refresh. */
	void SetAsset(const UCFModelAsset* InAsset);

	/** Refresh all displayed text from the current asset. */
	void Refresh();

private:
	const UCFModelAsset* Asset = nullptr;

	TSharedPtr<STextBlock> SchemaText;
	TSharedPtr<STextBlock> PluginText;
	TSharedPtr<STextBlock> EngineText;
};