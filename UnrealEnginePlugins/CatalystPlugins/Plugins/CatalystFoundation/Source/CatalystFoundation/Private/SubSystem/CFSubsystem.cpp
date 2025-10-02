// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "SubSystem/CFSubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCFSubsystem);

void UCFSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogCFSubsystem, Verbose, TEXT("CFSubsystem initialized"));
}

void UCFSubsystem::Deinitialize()
{
    UE_LOG(LogCFSubsystem, Verbose, TEXT("CFSubsystem deinitialized"));
    Super::Deinitialize();
}

UCFSubsystem* UCFSubsystem::Get(const UObject* WorldContextObject)
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
            return GI->GetSubsystem<UCFSubsystem>();
        }
        return nullptr;
    }

    if (UGameInstance* GI = World->GetGameInstance())
    {
        return GI->GetSubsystem<UCFSubsystem>();
    }
    return nullptr;
}
