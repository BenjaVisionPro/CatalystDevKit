#pragma once
#include "Modules/ModuleManager.h"

// Declare the editor module's log category (extern).
DECLARE_LOG_CATEGORY_EXTERN(LogCatalystFoundationEditor, Log, All);

class FCatalystFoundationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};