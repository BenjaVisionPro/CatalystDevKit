// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture.h"
#include "CCSettings.generated.h"


/** Atlas texture size must be power of 2 */
UENUM(BlueprintType, Category = CatalystConnect)
enum class ECCDiscoveryServerType :uint8
{
	SERVER_DEVELOPMENT = 0	UMETA(DisplayName = "Development"),
	SERVER_TESTING			UMETA(DisplayName = "Testing"),
	SERVER_PRODUCTION		UMETA(DisplayName = "Production"),
};


USTRUCT(BlueprintType)
struct CATALYSTCONNECT_API FCCServerSettings
{
	GENERATED_BODY()
public:
	/**
	 * Server Name
	 */
	UPROPERTY(EditAnywhere, config, Category = Server)
		FString serverName;
		
	/** Server Type */
	UPROPERTY(EditAnywhere, config, Category = Server)
		ECCDiscoveryServerType serverType = ECCDiscoveryServerType::SERVER_DEVELOPMENT;

	/** Server Address */
	UPROPERTY(EditAnywhere, config, Category = Server)
		FString serverAddress;
	
	/** Connect to server on startup */
	UPROPERTY(EditAnywhere, config, Category = Server)
		bool bConnectOnStartup = false;

};


// Catalyst:Connect Settings
UCLASS(config=Engine, defaultconfig)
class CATALYSTCONNECT_API UCCSettings :public UObject
{
	GENERATED_BODY()
public:
	// Automatic Key Negotiation
	UPROPERTY(EditAnywhere, config, Category = "Security")
		bool bAutomaticallyNegotiateKeys = true;
		
	// Path to key files for container secrets support
	UPROPERTY(EditAnywhere, config, Category = "Security")
		FDirectoryPath pathToKeyFiles;
	
	// Known DiscoveryServers
	UPROPERTY(EditAnywhere, config, Category = "DiscoveryServers", meta = (LongPackageName))
		TArray<FCCServerSettings> servers;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)override;
#endif

public:
	static bool GetAutomaticallyNegotiateKeys(const FName& InPackingTag);
    static FDirectoryPath GetPathToKeyFiles(const FName& InPackingTag);
    static TArray<FCCServerSettings> GetDiscoveryServers(const FName& InPackingTag);
};

// Catalyst:Connect Editor Settings @todo:save config in editor
UCLASS(config=Editor, defaultconfig)
class CATALYSTCONNECT_API UCCEditorSettings : public UObject
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)override;
	static bool GetConnectDiscoveryServersOnStartup();
#endif
	virtual bool IsEditorOnly()const override { return true; }
#if WITH_EDITORONLY_DATA
    // Connect to Development Server on Startup
	UPROPERTY(EditAnywhere, config, Category = "DiscoveryServers")
		bool bConnectDiscoveryServersOnStartup = true;

#endif
};
