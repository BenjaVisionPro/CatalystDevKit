// ============================================================================
// CatalystFoundationEditor — Module interface (legacy-free)
// ============================================================================

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"

// Declare the editor log category (defined in the .cpp)
DECLARE_LOG_CATEGORY_EXTERN(LogCFEditor, Log, All);

/**
 * Editor module for Catalyst Foundation.
 * AssetDefinitions own Add(+) placement; no AssetTools category registration here.
 */
class FCatalystFoundationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};