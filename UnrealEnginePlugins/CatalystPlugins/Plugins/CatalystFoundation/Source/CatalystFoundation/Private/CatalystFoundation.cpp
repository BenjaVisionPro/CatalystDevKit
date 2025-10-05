#include "CatalystFoundation.h"
#include "Log/CFLog.h"

DEFINE_LOG_CATEGORY(LogCF);

#define LOCTEXT_NAMESPACE "FCatalystFoundationModule"

void FCatalystFoundationModule::StartupModule()
{
    CF_INFO(TEXT("Catalyst Foundation module started."));
}

void FCatalystFoundationModule::ShutdownModule()
{
    CF_INFO(TEXT("Catalyst Foundation module shut down."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCatalystFoundationModule, CatalystFoundation)