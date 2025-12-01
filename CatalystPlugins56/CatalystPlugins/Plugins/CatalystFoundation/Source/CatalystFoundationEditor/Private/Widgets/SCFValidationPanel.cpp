// Copyright ...

#include "Widgets/SCFValidationPanel.h"

#include "Model/CFModelAsset.h"
#include "Validation/CFValidatable.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "SCFValidationPanel"

void SCFValidationPanel::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4)
		[
			SNew(SVerticalBox)

			// Toolbar: search + toggles + refresh
			+ SVerticalBox::Slot().AutoHeight().Padding(2)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().FillWidth(1.f).Padding(2)
				[
					SAssignNew(SearchBox, SSearchBox)
					.OnTextChanged(this, &SCFValidationPanel::OnFilterTextChanged)
					.HintText(LOCTEXT("SearchHint", "Filter messages..."))
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(2)
				[
					SAssignNew(ErrorsToggle, SCheckBox)
					.IsChecked(ECheckBoxState::Checked)
					.OnCheckStateChanged_Lambda([this](ECheckBoxState S){ OnToggleSeverity(ECFValidationSeverity::Error, S); })
					[
						SNew(STextBlock).Text(LOCTEXT("Errors", "Errors"))
					]
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(2)
				[
					SAssignNew(WarningsToggle, SCheckBox)
					.IsChecked(ECheckBoxState::Checked)
					.OnCheckStateChanged_Lambda([this](ECheckBoxState S){ OnToggleSeverity(ECFValidationSeverity::Warning, S); })
					[
						SNew(STextBlock).Text(LOCTEXT("Warnings", "Warnings"))
					]
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(2)
				[
					SAssignNew(InfosToggle, SCheckBox)
					.IsChecked(ECheckBoxState::Checked)
					.OnCheckStateChanged_Lambda([this](ECheckBoxState S){ OnToggleSeverity(ECFValidationSeverity::Info, S); })
					[
						SNew(STextBlock).Text(LOCTEXT("Infos", "Info"))
					]
				]
				+ SHorizontalBox::Slot().AutoWidth().Padding(2)
				[
					SNew(SButton)
					.Text(LOCTEXT("Refresh", "Refresh"))
					.OnClicked_Lambda([this]()
					{
						Refresh();
						return FReply::Handled();
					})
				]
			]

			// List
			+ SVerticalBox::Slot().FillHeight(1.f).Padding(2)
			[
				SAssignNew(ListView, SListView<TSharedPtr<FCFValidationMessage>>)
				.ListItemsSource(&Items)
				.OnGenerateRow(this, &SCFValidationPanel::OnGenerateRow)
				.SelectionMode(ESelectionMode::Single)
			]
		]
	];

	Refresh();
}

void SCFValidationPanel::SetAsset(const UCFModelAsset* InAsset)
{
	Asset = InAsset;
	Source = nullptr; // Asset-driven
}

void SCFValidationPanel::SetIssueSource(TFunction<void(TArray<FCFValidationMessage>&)> InSource)
{
	Source = MoveTemp(InSource);
	Asset = nullptr; // Source-driven
}

void SCFValidationPanel::Refresh()
{
	// Populate AllItems from Source or Asset
	AllItems.Reset();

	TArray<FCFValidationMessage> Raw;
	if (Source)
	{
		Source(Raw);
	}
	else if (Asset)
	{
		if (const ICFValidatable* V = Cast<ICFValidatable>(Asset))
		{
			V->CollectValidationMessages(Raw);
		}
	}

	for (const FCFValidationMessage& M : Raw)
	{
		AllItems.Add(MakeShared<FCFValidationMessage>(M));
	}

	RebuildItems();

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

void SCFValidationPanel::RebuildItems()
{
	Items.Reset();

	const bool WantError   = bShowErrors;
	const bool WantWarning = bShowWarnings;
	const bool WantInfo    = bShowInfos;

	for (const TSharedPtr<FCFValidationMessage>& Ptr : AllItems)
	{
		if (!Ptr.IsValid()) continue;
		const FCFValidationMessage& M = *Ptr;

		// Severity filter
		const bool PassSev =
			(M.Severity == ECFValidationSeverity::Error   && WantError) ||
			(M.Severity == ECFValidationSeverity::Warning && WantWarning) ||
			(M.Severity == ECFValidationSeverity::Info    && WantInfo);

		if (!PassSev) continue;

		// Text filter (search Summary + Detail + Code + Path)
		if (!TextFilter.IsEmpty())
		{
			const FString S = M.Summary.ToString();
			const FString D = M.Detail.ToString();
			const FString C = M.Code.ToString();
			const FString P = M.Path;

			if (!(S.Contains(TextFilter) || D.Contains(TextFilter) || C.Contains(TextFilter) || P.Contains(TextFilter)))
			{
				continue;
			}
		}

		Items.Add(Ptr);
	}
}

TSharedRef<ITableRow> SCFValidationPanel::OnGenerateRow(TSharedPtr<FCFValidationMessage> Item, const TSharedRef<STableViewBase>& OwnerTable) const
{
	FSlateColor Color;
	FText SevText;

	if (Item && Item->Severity == ECFValidationSeverity::Error)
	{
		Color = FSlateColor(FLinearColor(0.85f, 0.2f, 0.2f));
		SevText = LOCTEXT("SevError", "Error");
	}
	else if (Item && Item->Severity == ECFValidationSeverity::Warning)
	{
		Color = FSlateColor(FLinearColor(1.0f, 0.8f, 0.2f));
		SevText = LOCTEXT("SevWarn", "Warning");
	}
	else
	{
		Color = FSlateColor(FLinearColor(0.7f, 0.8f, 1.0f));
		SevText = LOCTEXT("SevInfo", "Info");
	}

	return SNew(STableRow<TSharedPtr<FCFValidationMessage>>, OwnerTable)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().Padding(0,0,6,0)
			[
				SNew(STextBlock).Text(SevText).ColorAndOpacity(Color)
			]
			+ SHorizontalBox::Slot().FillWidth(1.f)
			[
				SNew(STextBlock).Text(Item.IsValid() ? Item->Summary : FText())
			]
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(STextBlock)
			.Text(Item.IsValid() ? Item->Detail : FText())
			.WrapTextAt(600.f)
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(STextBlock)
			.Text_Lambda([Item]()
			{
				if (!Item.IsValid()) return FText();
				FString Meta;
				if (!Item->Code.IsNone())
				{
					Meta += FString::Printf(TEXT("[%s] "), *Item->Code.ToString());
				}
				if (!Item->Path.IsEmpty())
				{
					Meta += Item->Path;
				}
				return Meta.IsEmpty() ? FText() : FText::FromString(Meta);
			})
			.ColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f)))
		]
	];
}

void SCFValidationPanel::OnFilterTextChanged(const FText& NewText)
{
	TextFilter = NewText.ToString();
	RebuildItems();
	if (ListView) ListView->RequestListRefresh();
}

void SCFValidationPanel::OnToggleSeverity(ECFValidationSeverity Sev, ECheckBoxState NewState)
{
	const bool bOn = (NewState == ECheckBoxState::Checked);
	switch (Sev)
	{
	case ECFValidationSeverity::Error:   bShowErrors   = bOn; break;
	case ECFValidationSeverity::Warning: bShowWarnings = bOn; break;
	case ECFValidationSeverity::Info:    bShowInfos    = bOn; break;
	}
	RebuildItems();
	if (ListView) ListView->RequestListRefresh();
}

#undef LOCTEXT_NAMESPACE