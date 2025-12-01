// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "SubSystem/CLSubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCESubsystem);

void UCLSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogCESubsystem, Verbose, TEXT("CLSubsystem initialized"));
}

void UCLSubsystem::Deinitialize()
{
    UE_LOG(LogCESubsystem, Verbose, TEXT("CLSubsystem deinitialized"));
    Super::Deinitialize();
}

UCLSubsystem* UCLSubsystem::Get(const UObject* WorldContextObject)
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
            return GI->GetSubsystem<UCLSubsystem>();
        }
        return nullptr;
    }

    if (UGameInstance* GI = World->GetGameInstance())
    {
        return GI->GetSubsystem<UCLSubsystem>();
    }
    return nullptr;
}
