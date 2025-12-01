/**
 * @file SCFVersionStatusWidget.cpp
 * @brief Displays plugin / schema / engine version status for a model asset.
 *
 * Copyright © 2024 Benjability Pty Ltd.
 */

#include "Widgets/SCFVersionStatusWidget.h"
#include "Model/CFModelAsset.h"

#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "SCFVersionStatusWidget"

void SCFVersionStatusWidget::Construct(const FArguments& InArgs, UCFModelAsset* InAsset)
{
	Asset = InAsset;

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(SchemaText, STextBlock)
				.Text(LOCTEXT("SchemaLabel", "Schema: —"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(PluginText, STextBlock)
				.Text(LOCTEXT("PluginLabel", "Plugin: —"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(EngineText, STextBlock)
				.Text(LOCTEXT("EngineLabel", "Engine: —"))
			]
		]
	];

	Refresh();
}

void SCFVersionStatusWidget::SetAsset(const UCFModelAsset* InAsset)
{
	Asset = InAsset;
	Refresh();
}

void SCFVersionStatusWidget::Refresh()
{
	if (!Asset)
	{
		if (SchemaText) SchemaText->SetText(LOCTEXT("NoAssetSchema", "Schema: —"));
		if (PluginText) PluginText->SetText(LOCTEXT("NoAssetPlugin", "Plugin: —"));
		if (EngineText) EngineText->SetText(LOCTEXT("NoAssetEngine", "Engine: —"));
		return;
	}

	const int32 Schema = Asset->GetPublicSchemaVersion();
	const FString Plugin = Asset->GetPublicPluginNameForPaths();
	const FString Engine = Asset->Version.EngineVersion;

	if (SchemaText)
		SchemaText->SetText(FText::Format(LOCTEXT("SchemaFmt", "Schema: {0}"), FText::AsNumber(Schema)));

	if (PluginText)
		PluginText->SetText(FText::Format(LOCTEXT("PluginFmt", "Plugin: {0}"), FText::FromString(Plugin)));

	if (EngineText)
		EngineText->SetText(FText::Format(LOCTEXT("EngineFmt", "Engine: {0}"), FText::FromString(Engine)));
}

#undef LOCTEXT_NAMESPACE