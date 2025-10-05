#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UCFModelAsset;
class IDetailsView;

/**
 * Base editor toolkit for Catalyst model assets.
 * Feature plugins can subclass if they need custom tabs/menus, or they can
 * just call InitModelEditor() with their asset to get a Details + Validation UI.
 */
class CATALYSTFOUNDATIONEDITOR_API FCFModelEditorToolkit : public FAssetEditorToolkit
{
public:
	FCFModelEditorToolkit();
	virtual ~FCFModelEditorToolkit() override;

	/** Initialize the editor for a specific model asset. */
	void InitModelEditor(UCFModelAsset* InAsset,
		EToolkitMode::Type Mode,
		const TSharedPtr<class IToolkitHost>& InitToolkitHost);

	// ------------- FAssetEditorToolkit -------------
	virtual FName   GetToolkitFName() const override;
	virtual FText   GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

protected:
	// ------------- Tab management -------------
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	TSharedRef<class SDockTab> SpawnDetailsTab(const class FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnValidationTab(const class FSpawnTabArgs& Args);

	/** Build the DetailsView for the current asset. */
	void BuildDetailsPanel();

protected:
	// Current asset being edited (never null after Init).
	TObjectPtr<UCFModelAsset> EditingAsset = nullptr;

	// Details
	TSharedPtr<IDetailsView> DetailsView;

	// Tab IDs
	static const FName DetailsTabId;
	static const FName ValidationTabId;
};