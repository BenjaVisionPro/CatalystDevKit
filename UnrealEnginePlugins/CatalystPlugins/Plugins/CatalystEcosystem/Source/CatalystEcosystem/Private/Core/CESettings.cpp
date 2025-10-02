// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Core/CESettings.h"
#include "CatalystEcosystem.h"

#if WITH_EDITOR
void UCESettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (auto Property = PropertyChangedEvent.Property)
	{
		auto PropertyName = Property->GetFName();
		
		// Do any updates that may be needed
	}
}
#endif
bool UCESettings::GetAutomaticallyNegotiateKeys(const FName& InPackingTag)
{
	return GetDefault<UCESettings>()->bAutomaticallyNegotiateKeys;
}

FDirectoryPath UCESettings::GetPathToKeyFiles(const FName& InPackingTag)
{
	return GetDefault<UCESettings>()->pathToKeyFiles;
}

TArray<FCEServerSettings> UCESettings::GetDiscoveryServers(const FName& InPackingTag)
{
	return GetDefault<UCESettings>()->servers;
}


#if WITH_EDITOR
void UCEEditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	auto MemberProperty = PropertyChangedEvent.MemberProperty;
	auto Property = PropertyChangedEvent.Property;
	if (MemberProperty && Property)
	{
		// Do any updates that may be needed
	}
}

void UCEEditorSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
bool UCEEditorSettings::GetConnectDiscoveryServersOnStartup()
{
	return GetDefault<UCEEditorSettings>()->bConnectDiscoveryServersOnStartup;
}
#endif
