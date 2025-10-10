// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Core/__PREFIX__Settings.h"
#include "__PLUGIN_NAME__.h"

#if WITH_EDITOR
void U__PREFIX__Settings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (auto Property = PropertyChangedEvent.Property)
	{
		auto PropertyName = Property->GetFName();
		
		// Do any updates that may be needed
	}
}
#endif
bool U__PREFIX__Settings::GetAutomaticallyNegotiateKeys(const FName& InPackingTag)
{
	return GetDefault<U__PREFIX__Settings>()->bAutomaticallyNegotiateKeys;
}

FDirectoryPath U__PREFIX__Settings::GetPathToKeyFiles(const FName& InPackingTag)
{
	return GetDefault<U__PREFIX__Settings>()->pathToKeyFiles;
}

TArray<F__PREFIX__ServerSettings> U__PREFIX__Settings::GetDiscoveryServers(const FName& InPackingTag)
{
	return GetDefault<U__PREFIX__Settings>()->servers;
}


#if WITH_EDITOR
void U__PREFIX__EditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	auto MemberProperty = PropertyChangedEvent.MemberProperty;
	auto Property = PropertyChangedEvent.Property;
	if (MemberProperty && Property)
	{
		// Do any updates that may be needed
	}
}

void U__PREFIX__EditorSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
bool U__PREFIX__EditorSettings::GetConnectDiscoveryServersOnStartup()
{
	return GetDefault<U__PREFIX__EditorSettings>()->bConnectDiscoveryServersOnStartup;
}
#endif
