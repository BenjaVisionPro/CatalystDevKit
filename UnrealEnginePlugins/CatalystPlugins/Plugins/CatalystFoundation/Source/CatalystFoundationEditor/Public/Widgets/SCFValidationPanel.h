// Copyright ...

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Validation/CFValidationTypes.h"

class UCFModelAsset;
template <typename ItemType> class SListView;
class SSearchBox;
class SCheckBox;

/**
 * Lightweight validation panel:
 * - Shows FCFValidationMessage items
 * - Filter by severity + text
 * - Manual Refresh()
 */
class CATALYSTFOUNDATIONEDITOR_API SCFValidationPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCFValidationPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** Provide an object to validate (usually a UCFModelAsset). */
	void SetAsset(const UCFModelAsset* InAsset);

	/** Optional: provide a custom source hook if not using SetAsset. */
	void SetIssueSource(TFunction<void(TArray<FCFValidationMessage>& OutMessages)> InSource);

	/** Rebuild the list from the current source + filters. */
	void Refresh();

private:
	// UI helpers
	void RebuildItems();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FCFValidationMessage> Item, const TSharedRef<STableViewBase>& OwnerTable) const;
	void OnFilterTextChanged(const FText& NewText);
	void OnToggleSeverity(ECFValidationSeverity Sev, ECheckBoxState NewState);

private:
	// Source
	const UCFModelAsset* Asset = nullptr;
	TFunction<void(TArray<FCFValidationMessage>&)> Source; // if set, overrides Asset

	// Data
	TArray<TSharedPtr<FCFValidationMessage>> Items;     // filtered
	TArray<TSharedPtr<FCFValidationMessage>> AllItems;  // raw

	// Filters
	bool bShowErrors   = true;
	bool bShowWarnings = true;
	bool bShowInfos    = true;
	FString TextFilter;

	// Widgets
	TSharedPtr<SListView<TSharedPtr<FCFValidationMessage>>> ListView;
	TSharedPtr<SSearchBox> SearchBox;
	TSharedPtr<SCheckBox> ErrorsToggle;
	TSharedPtr<SCheckBox> WarningsToggle;
	TSharedPtr<SCheckBox> InfosToggle;
};