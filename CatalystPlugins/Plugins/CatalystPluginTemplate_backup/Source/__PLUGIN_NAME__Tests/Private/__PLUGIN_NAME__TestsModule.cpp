#include "Modules/ModuleManager.h"
class FCatalystEcosystemTestsModule : public IModuleInterface { public: virtual void StartupModule() override {} virtual void ShutdownModule() override {} };
IMPLEMENT_MODULE(FCatalystEcosystemTestsModule, __PLUGIN_NAME__Tests)
