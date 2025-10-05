#include "CatalystFoundation.h"

// Define the runtime module's log category exactly once.
DEFINE_LOG_CATEGORY(LogCatalystFoundation);

void FCatalystFoundationModule::StartupModule() {}
void FCatalystFoundationModule::ShutdownModule() {}

IMPLEMENT_MODULE(FCatalystFoundationModule, CatalystFoundation)