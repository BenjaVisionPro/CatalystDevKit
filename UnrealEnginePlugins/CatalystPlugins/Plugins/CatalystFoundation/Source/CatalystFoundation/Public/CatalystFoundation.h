#pragma once
#include "Modules/ModuleManager.h"

CATALYSTFOUNDATION_API DECLARE_LOG_CATEGORY_EXTERN(LogCF, Log, All);

class FCatalystFoundationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};