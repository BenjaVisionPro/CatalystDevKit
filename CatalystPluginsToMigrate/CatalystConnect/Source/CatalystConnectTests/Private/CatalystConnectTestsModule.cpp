#include "Modules/ModuleManager.h"
class FCatalystConnectTestsModule : public IModuleInterface { public: virtual void StartupModule() override {} virtual void ShutdownModule() override {} };
IMPLEMENT_MODULE(FCatalystConnectTestsModule, CatalystConnectTests)
