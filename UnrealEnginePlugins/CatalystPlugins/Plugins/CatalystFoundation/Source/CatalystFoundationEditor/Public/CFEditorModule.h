// ============================================================================
// CatalystFoundationEditor — Module & Asset Category
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

// Editor log category (declared here, defined in .cpp)
DECLARE_LOG_CATEGORY_EXTERN(LogCFEditor, Log, All);

/**
 * Returns the shared "Catalyst" asset category for Content Browser integration.
 * Call FCFEditorAssetCategory::Get() when implementing AssetTypeActions.
 */
class CATALYSTFOUNDATIONEDITOR_API FCFEditorAssetCategory
{
public:
	/** Category bit used by AssetTypeActions (valid after StartupModule). */
	static EAssetTypeCategories::Type Get();

	/** Registered once during module startup. Safe to call multiple times. */
	static void Register();

private:
	static EAssetTypeCategories::Type CatalystCategory;
};

/** Editor module for Catalyst Foundation. Registers asset category on startup. */
class FCatalystFoundationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};