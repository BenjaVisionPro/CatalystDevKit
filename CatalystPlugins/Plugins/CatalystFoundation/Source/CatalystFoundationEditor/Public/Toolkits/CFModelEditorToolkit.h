/**
 * @file CFModelEditorToolkit.h
 * @brief Base asset editor for Catalyst model assets. Hosts Details + Validation
 *        tabs and (when in PIE/Game) listens to the runtime model service.
 */

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Services/CFAbstractModelService.h" // UCFAbstractModelService, FCFModelError

class UCFModelAsset;
class IDetailsView;
class SCFValidationPanel;
class SCFVersionStatusWidget;

/**
 * Base editor toolkit for Catalyst model assets.
 * Orchestrates refresh across Details/Validation tabs by listening
 * to the runtime model service (if present in PIE/Game).
 */
class CATALYSTFOUNDATIONEDITOR_API FCFModelEditorToolkit : public FAssetEditorToolkit
{
public:
	FCFModelEditorToolkit();
	virtual ~FCFModelEditorToolkit() override;

	void InitModelEditor(
		UCFModelAsset* InAsset,
		EToolkitMode::Type Mode,
		const TSharedPtr<class IToolkitHost>& InitToolkitHost);

	// ------------- FAssetEditorToolkit -------------
	virtual FName        GetToolkitFName() const override;
	virtual FText        GetBaseToolkitName() const override;
	virtual FString      GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

protected:
	// ------------- Tab management -------------
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	TSharedRef<class SDockTab> SpawnDetailsTab(const class FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnValidationTab(const class FSpawnTabArgs& Args);

	void BuildDetailsPanel();
	void TryBindRuntimeService();

	void BindRuntimeDelegates();
	void UnbindRuntimeDelegates();

	void RefreshAllUI(UCFModelAsset* LiveModel, bool bIsReload);

	// ---- Toolbar / Menu actions ----
	void HandleExportJson();

	// ---- Runtime service handlers ----
	void HandleModelReady(UCFModelAsset* LiveModel);
	void HandleModelReloaded(UCFModelAsset* LiveModel);
	void HandleModelUpdated();
	void HandleModelError(const FString& Message);
	void HandleModelErrorEx(const FCFModelError& Error);

protected:
	TObjectPtr<UCFModelAsset> EditingAsset = nullptr;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<SCFValidationPanel> ValidationPanel;
	TSharedPtr<SCFVersionStatusWidget> VersionBanner;
	TWeakObjectPtr<UCFAbstractModelService> RuntimeService;

	static const FName DetailsTabId;
	static const FName ValidationTabId;
};