#pragma once
#include "Modules/ModuleManager.h"

// Declare the runtime module's log category (extern).
DECLARE_LOG_CATEGORY_EXTERN(LogCatalystFoundation, Log, All);

class FCatalystFoundationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};