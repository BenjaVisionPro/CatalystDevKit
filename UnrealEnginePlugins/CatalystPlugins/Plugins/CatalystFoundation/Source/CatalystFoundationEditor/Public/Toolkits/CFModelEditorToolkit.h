/**
 * @file CFModelEditorToolkit.h
 * @brief Base asset editor for Catalyst model assets. Hosts Details + Validation
 *        tabs and (when in PIE/Game) listens to the runtime model service to
 *        keep editor UI in sync with the live model.
 *
 * Copyright © 2022 Jupiter Jones
 * Copyright © 2024 Benjability Pty Ltd.
 * All rights and remedies reserved.
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

	/** Initialize the editor for a specific model asset. */
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

	/** Build the DetailsView for the current asset. */
	void BuildDetailsPanel();

	/** Try to discover a PIE/Game world and bind model-service delegates if available. */
	void TryBindRuntimeService();

	/** Bind/unbind to the runtime model service delegates. */
	void BindRuntimeDelegates();
	void UnbindRuntimeDelegates();

	/** Centralized UI refresh conductor. */
	void RefreshAllUI(UCFModelAsset* LiveModel, bool bIsReload);

	// ---- Toolbar / Menu JSON actions ----
	void HandleExportJson();
	void HandleReloadJson();

	// ---- Runtime service delegate handlers ----
	void HandleModelReady(UCFModelAsset* LiveModel);
	void HandleModelReloaded(UCFModelAsset* LiveModel);
	void HandleModelUpdated();
	void HandleModelError(const FString& Message);
	void HandleModelErrorEx(const FCFModelError& Error); // typed error payload

protected:
	/** Current asset being edited (never null after Init). */
	TObjectPtr<UCFModelAsset> EditingAsset = nullptr;

	/** Details panel. */
	TSharedPtr<IDetailsView> DetailsView;

	/** Validation UI pieces. */
	TSharedPtr<SCFValidationPanel>     ValidationPanel;
	TSharedPtr<SCFVersionStatusWidget> VersionBanner;

	/** Optional runtime service (valid in PIE/Game worlds). */
	TWeakObjectPtr<UCFAbstractModelService> RuntimeService;

	// Tab IDs
	static const FName DetailsTabId;
	static const FName ValidationTabId;
};