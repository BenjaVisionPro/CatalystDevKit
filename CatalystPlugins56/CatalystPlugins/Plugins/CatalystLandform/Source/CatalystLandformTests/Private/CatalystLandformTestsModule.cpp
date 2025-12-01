#include "Modules/ModuleManager.h"
class FCatalystLandformTestsModule : public IModuleInterface { 
	public: 
		virtual void StartupModule() override {} 
		virtual void ShutdownModule() override {} 
};
IMPLEMENT_MODULE(FCatalystLandformTestsModule, CatalystLandformTests)
