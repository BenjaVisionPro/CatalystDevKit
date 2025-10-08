#pragma once

#include "CoreMinimal.h"
#include "UI/Panels/SCFAbstractPanel.h"
#include "Widgets/Views/SListView.h"

struct FCEListRow
{
	FString Name;
};

using FCEListRowPtr = TSharedPtr<FCEListRow>;

/**
 * Shared editor layout base:
 * - Collapsible/searchable list on the left
 * - Details panel on the right
 * Subclass this and provide data + details UI.
 */
class SCFEditorPanel : public SCFAbstractPanel
{
public:
	SLATE_BEGIN_ARGS(SCFEditorPanel) {}
		SLATE_ATTRIBUTE(FText, Title)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	// For subclasses to provide their own content/behavior
protected:
	virtual void GatherInitialItems(TArray<FCEListRowPtr>& OutItems) {}
	virtual TSharedRef<SWidget> BuildDetailsFor(const FCEListRowPtr& Item);

protected:
	// UI callbacks
	void OnFilterTextChanged(const FText& InText);
	void Refilter();
	TSharedRef<ITableRow> OnGenerateRow(FCEListRowPtr Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnSelectionChanged(FCEListRowPtr Item, ESelectInfo::Type);

private:
	TSharedRef<SWidget> BuildEditorBody();

private:
	// State
	TArray<FCEListRowPtr> SourceItems;
	TArray<FCEListRowPtr> FilteredItems;

	TSharedPtr<SSearchBox> SearchBox;
	TSharedPtr<SListView<FCEListRowPtr>> ListView;
	TSharedPtr<SBorder> DetailsHost;

	// Left column width (0=collapsed .. 0.35 typical)
	float LeftWidth = 0.28f;
	bool  bCollapsed = false;
};