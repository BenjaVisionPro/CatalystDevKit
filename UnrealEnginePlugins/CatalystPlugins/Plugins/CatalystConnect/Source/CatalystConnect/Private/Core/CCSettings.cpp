// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Core/CCSettings.h"
#include "CatalystConnect.h"

#if WITH_EDITOR
void UCCSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (auto Property = PropertyChangedEvent.Property)
	{
		auto PropertyName = Property->GetFName();
		
		// Do any updates that may be needed
	}
}
#endif
bool UCCSettings::GetAutomaticallyNegotiateKeys(const FName& InPackingTag)
{
	return GetDefault<UCCSettings>()->bAutomaticallyNegotiateKeys;
}

FDirectoryPath UCCSettings::GetPathToKeyFiles(const FName& InPackingTag)
{
	return GetDefault<UCCSettings>()->pathToKeyFiles;
}

TArray<FCCServerSettings> UCCSettings::GetDiscoveryServers(const FName& InPackingTag)
{
	return GetDefault<UCCSettings>()->servers;
}


#if WITH_EDITOR
void UCCEditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	auto MemberProperty = PropertyChangedEvent.MemberProperty;
	auto Property = PropertyChangedEvent.Property;
	if (MemberProperty && Property)
	{
		// Do any updates that may be needed
	}
}

void UCCEditorSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
bool UCCEditorSettings::GetConnectDiscoveryServersOnStartup()
{
	return GetDefault<UCCEditorSettings>()->bConnectDiscoveryServersOnStartup;
}
#endif
