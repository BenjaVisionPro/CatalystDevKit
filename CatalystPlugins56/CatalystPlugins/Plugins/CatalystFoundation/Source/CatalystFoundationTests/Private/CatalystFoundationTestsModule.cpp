#include "Modules/ModuleManager.h"
class FCatalystFoundationTestsModule : public IModuleInterface { 
	public: 
	    virtual void StartupModule() override {} 
	    virtual void ShutdownModule() override {} 
};
IMPLEMENT_MODULE(FCatalystFoundationTestsModule, CatalystFoundationTests)
