#include "Services/CFAbstractModelService.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UCFAbstractModelService::Initialize(FSubsystemCollectionBase& Collection)
{
    FString Err;
    RefreshModel(Err);
}

bool UCFAbstractModelService::RefreshModel(FString& OutError)
{
    if (Model.IsValid())
    {
        if (!Model->TryLoadFromDiskJson(OutError))
        {
            return LoadSeedIntoModel(OutError);
        }
        return true;
    }

    if (!LoadSeedIntoModel(OutError))
    {
        return false;
    }

    if (!Model->TryLoadFromDiskJson(OutError))
    {
        // keep seed
    }
    return true;
}

bool UCFAbstractModelService::SaveModel(FString& OutError) const
{
    if (!Model.IsValid())
    {
        OutError = TEXT("No model loaded.");
        return false;
    }
    return Model->SaveToDiskJson(OutError);
}

void UCFAbstractModelService::SetModel(UCFModelRoot* NewModel)
{
    Model.Reset();
    if (NewModel)
    {
        Model = TStrongObjectPtr<UCFModelRoot>(NewModel);
    }
}

FString UCFAbstractModelService::GetPluginName() const
{
    if (Model.IsValid())
    {
        return Model->GetOwningPluginName();
    }
    if (TSoftObjectPtr<UCFModelRoot> Seed = GetSeedAssetSoft())
    {
        if (Seed.IsValid())
        {
            return Seed.Get()->GetOwningPluginName();
        }
    }
    return TEXT("UnknownPlugin");
}

bool UCFAbstractModelService::LoadSeedIntoModel(FString& OutError)
{
    TSoftObjectPtr<UCFModelRoot> SeedSoft = GetSeedAssetSoft();
    if (!SeedSoft.IsValid())
    {
        SeedSoft.LoadSynchronous();
    }
    UCFModelRoot* Seed = SeedSoft.Get();
    if (!Seed)
    {
        OutError = TEXT("Failed to load seed model asset.");
        return false;
    }
    UCFModelRoot* Instance = DuplicateObject<UCFModelRoot>(Seed, GetTransientPackage());
    if (!Instance)
    {
        OutError = TEXT("Failed to duplicate seed model.");
        return false;
    }
    SetModel(Instance);
    return true;
}
