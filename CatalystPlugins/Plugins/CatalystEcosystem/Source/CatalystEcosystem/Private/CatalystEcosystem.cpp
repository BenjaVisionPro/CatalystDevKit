// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CatalystEcosystem.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "FCatalystEcosystemModule"
DEFINE_LOG_CATEGORY(LogCE);


void FCatalystEcosystemModule::StartupModule()
{

}

void FCatalystEcosystemModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCatalystEcosystemModule, CatalystEcosystem)
