// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CatalystPlugin.h"

UCatalystPlugin::UCatalystPlugin()
{
    // Constructor logic here
}

void UCatalystPlugin::MyCustomFunction()
{
    // Function logic here
}

void UCatalystPlugin::FindCatalystPlugins()
{
    if(bCatalystPluginsInitialized)
    {
        return;
    }
    
    for(TObjectIterator<UClass> It; It; ++It)
    {
        if(It->ImplementsInterface(UCatalystPlugin::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
        {
            CatalystPlugins.Add(*It);
        }
    }
    
    CatalystPlugins.Sort();
    bCatalystPluginsInitialized = true;
}
