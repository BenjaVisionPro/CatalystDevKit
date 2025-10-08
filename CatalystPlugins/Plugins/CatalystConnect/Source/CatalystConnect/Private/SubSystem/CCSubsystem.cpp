// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "SubSystem/CCSubsystem.h"
#include "Connection/UBVCConnection.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCCSubsystem);

void UCCSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogCCSubsystem, Verbose, TEXT("CCSubsystem initialized"));
}

void UCCSubsystem::Deinitialize()
{
    UE_LOG(LogCCSubsystem, Verbose, TEXT("CCSubsystem deinitialized"));
    Super::Deinitialize();
}

UCCSubsystem* UCCSubsystem::Get(const UObject* WorldContextObject)
{
    if (!WorldContextObject)
    {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World)
    {
        // Try to resolve via outer chain if no world yet
        if (const UGameInstance* GI = Cast<UGameInstance>(WorldContextObject->GetOuter()))
        {
            return GI->GetSubsystem<UCCSubsystem>();
        }
        return nullptr;
    }

    if (UGameInstance* GI = World->GetGameInstance())
    {
        return GI->GetSubsystem<UCCSubsystem>();
    }
    return nullptr;
}

UBVCConnection* UCCSubsystem::CreateConnection(const FBVCConnectionConfig& Config)
{
    UGameInstance* GI = GetGameInstance();
    if (!GI)
    {
        UE_LOG(LogCCSubsystem, Warning, TEXT("CreateConnection failed: no GameInstance"));
        return nullptr;
    }

    UBVCConnection* Conn = NewObject<UBVCConnection>(GI);
    if (!Conn)
    {
        UE_LOG(LogCCSubsystem, Warning, TEXT("CreateConnection failed: NewObject returned null"));
        return nullptr;
    }

    Conn->InitializeConnection(Config);
    return Conn;
}
