// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CatalystConnect.h"
#include "Modules/ModuleManager.h"
#include "DataConfig/DcEnv.h"
#include "DataConfig/Automation/DcAutomationUtils.h"


#define LOCTEXT_NAMESPACE "FCatalystConnectModule"
//DEFINE_LOG_CATEGORY(LogCatalystConnect);


void FCatalystConnectModule::StartupModule()
{
	// StartUp DataConfig
    DcStartUp(EDcInitializeAction::SetAsConsole);
    // dump a FVector to try it out
    FVector Vec(1.0f, 2.0f, 3.0f);
    FDcPropertyDatum VecDatum(TBaseStructure<FVector>::Get(), &Vec);

    DcAutomationUtils::DumpToLog(VecDatum);
}

void FCatalystConnectModule::ShutdownModule()
{
	// Shutdown DataConfig
	DcShutDown();
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCatalystConnectModule, CatalystConnect)
