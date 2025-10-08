#include "UI/Panels/SCFEditorPanel.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Styles/CFEditorFontsStyle.h"

void SCFEditorPanel::Construct(const FArguments& InArgs)
{
	// Seed with something so it renders immediately; subclasses can override GatherInitialItems
	GatherInitialItems(SourceItems);
	FilteredItems = SourceItems;

	SCFAbstractPanel::Construct(
		SCFAbstractPanel::FArguments()
		.Title(InArgs._Title.IsSet() ? InArgs._Title : FText::FromString(TEXT("Editor")))
		.Content()
		[
			BuildEditorBody()
		]
	);
}

TSharedRef<SWidget> SCFEditorPanel::BuildEditorBody()
{
	return
	SNew(SSplitter)
	+ SSplitter::Slot()
	.Value(TAttribute<float>::Create(TAttribute<float>::FGetter::CreateLambda([this]{ return bCollapsed ? 0.0f : LeftWidth; })))
	[
		SNew(SVerticalBox)

		// Controls row (collapse toggle + search)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f, 0.f, 0.f, 6.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
				{
					bCollapsed = (NewState == ECheckBoxState::Checked);
					if (ListView.IsValid()) { ListView->RequestListRefresh(); }
				})
				.IsChecked_Lambda([this]{ return bCollapsed ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("Collapse")))
				]
			]
			+ SHorizontalBox::Slot().FillWidth(1.f).Padding(6.f,0.f,0.f,0.f)
			[
				SAssignNew(SearchBox, SSearchBox)
				.OnTextChanged(this, &SCFEditorPanel::OnFilterTextChanged)
			]
		]

		// List
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SAssignNew(ListView, SListView<FCEListRowPtr>)
			.ListItemsSource(&FilteredItems)
			.OnGenerateRow(this, &SCFEditorPanel::OnGenerateRow)
			.OnSelectionChanged(this, &SCFEditorPanel::OnSelectionChanged)
		]
	]

	// Right: details host
	+ SSplitter::Slot()
	.Value(1.f - LeftWidth)
	[
		SAssignNew(DetailsHost, SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.DarkGroupBorder"))
		[
			SNew(STextBlock)
			.Font(FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::FontBody12))
			.Text(FText::FromString(TEXT("Select an item…")))
		]
	];
}

void SCFEditorPanel::OnFilterTextChanged(const FText& InText)
{
	Refilter();
}

void SCFEditorPanel::Refilter()
{
	const FString Filter = SearchBox.IsValid() ? SearchBox->GetText().ToString() : FString();

	FilteredItems.Reset();
	for (const FCEListRowPtr& Row : SourceItems)
	{
		if (Filter.IsEmpty() || Row->Name.Contains(Filter, ESearchCase::IgnoreCase))
		{
			FilteredItems.Add(Row);
		}
	}

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SCFEditorPanel::OnGenerateRow(FCEListRowPtr Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FCEListRowPtr>, OwnerTable)
	[
		SNew(STextBlock).Text(FText::FromString(Item.IsValid() ? Item->Name : TEXT("<null>")))
	];
}

void SCFEditorPanel::OnSelectionChanged(FCEListRowPtr Item, ESelectInfo::Type)
{
	if (!DetailsHost.IsValid()) return;

	DetailsHost->SetContent(
		BuildDetailsFor(Item)
	);
}

TSharedRef<SWidget> SCFEditorPanel::BuildDetailsFor(const FCEListRowPtr& Item)
{
	return
	SNew(SVerticalBox)
	+ SVerticalBox::Slot().AutoHeight().Padding(8.f)
	[
		SNew(STextBlock)
		.Font(FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::FontDisplay32))
		.Text(FText::FromString(Item.IsValid() ? Item->Name : TEXT("Details")))
	]
	+ SVerticalBox::Slot().FillHeight(1.f).Padding(8.f)
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
	];
}