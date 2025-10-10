// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "SubSystem/__PREFIX__Subsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCESubsystem);

void U__PREFIX__Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogCESubsystem, Verbose, TEXT("__PREFIX__Subsystem initialized"));
}

void U__PREFIX__Subsystem::Deinitialize()
{
    UE_LOG(LogCESubsystem, Verbose, TEXT("__PREFIX__Subsystem deinitialized"));
    Super::Deinitialize();
}

U__PREFIX__Subsystem* U__PREFIX__Subsystem::Get(const UObject* WorldContextObject)
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
            return GI->GetSubsystem<U__PREFIX__Subsystem>();
        }
        return nullptr;
    }

    if (UGameInstance* GI = World->GetGameInstance())
    {
        return GI->GetSubsystem<U__PREFIX__Subsystem>();
    }
    return nullptr;
}
