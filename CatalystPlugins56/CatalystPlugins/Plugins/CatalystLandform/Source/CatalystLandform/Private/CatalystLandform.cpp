// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CatalystLandform.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "FCatalystLandformModule"
DEFINE_LOG_CATEGORY(LogCL);


void FCatalystLandformModule::StartupModule()
{

}

void FCatalystLandformModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCatalystLandformModule, CatalystLandform)
