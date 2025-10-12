// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Core/CLSettings.h"
#include "CatalystLandform.h"

#if WITH_EDITOR
void UCLSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (auto Property = PropertyChangedEvent.Property)
	{
		auto PropertyName = Property->GetFName();
		
		// Do any updates that may be needed
	}
}
#endif
bool UCLSettings::GetAutomaticallyNegotiateKeys(const FName& InPackingTag)
{
	return GetDefault<UCLSettings>()->bAutomaticallyNegotiateKeys;
}

FDirectoryPath UCLSettings::GetPathToKeyFiles(const FName& InPackingTag)
{
	return GetDefault<UCLSettings>()->pathToKeyFiles;
}

TArray<FCLServerSettings> UCLSettings::GetDiscoveryServers(const FName& InPackingTag)
{
	return GetDefault<UCLSettings>()->servers;
}


#if WITH_EDITOR
void UCLEditorSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	auto MemberProperty = PropertyChangedEvent.MemberProperty;
	auto Property = PropertyChangedEvent.Property;
	if (MemberProperty && Property)
	{
		// Do any updates that may be needed
	}
}

void UCLEditorSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
bool UCLEditorSettings::GetConnectDiscoveryServersOnStartup()
{
	return GetDefault<UCLEditorSettings>()->bConnectDiscoveryServersOnStartup;
}
#endif
