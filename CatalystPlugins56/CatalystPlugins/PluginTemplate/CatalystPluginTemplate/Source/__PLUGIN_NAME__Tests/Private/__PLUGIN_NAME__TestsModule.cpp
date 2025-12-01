#include "Modules/ModuleManager.h"
class F__PLUGIN_NAME__TestsModule : public IModuleInterface { 
	public: 
		virtual void StartupModule() override {} 
		virtual void ShutdownModule() override {} 
};
IMPLEMENT_MODULE(F__PLUGIN_NAME__TestsModule, __PLUGIN_NAME__Tests)
