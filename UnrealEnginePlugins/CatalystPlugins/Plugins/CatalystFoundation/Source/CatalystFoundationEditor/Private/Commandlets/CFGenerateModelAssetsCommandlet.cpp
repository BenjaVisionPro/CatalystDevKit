// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "Commandlets/CFGenerateModelAssetsCommandlet.h"

#include "Model/CFModelAsset.h"
#include "Interfaces/IPluginManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

UCFGenerateModelAssetsCommandlet::UCFGenerateModelAssetsCommandlet()
{
	IsClient       = false;
	IsEditor       = true;
	LogToConsole   = true;
	ShowErrorCount = true;

	HelpDescription = TEXT(
		"Generate model assets from JSON files under <PluginRoot>/Model (or -InputDir).\n")
		TEXT("-Plugin=<Name> -AssetClass=/Script/Module.Class [-Overwrite] [-DryRun] [-InputDir=Model]");
}

// Load a UClass from a soft path like /Script/Module.ClassName
static bool LoadClassFromPath(const FString& ClassPath, UClass*& OutClass)
{
	OutClass = nullptr;
	if (ClassPath.IsEmpty()) return false;

	UClass* C = StaticLoadClass(UObject::StaticClass(), /*InOuter*/nullptr, *ClassPath);
	if (!C)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load class from '%s'."), *ClassPath);
		return false;
	}
	OutClass = C;
	return true;
}

int32 UCFGenerateModelAssetsCommandlet::Main(const FString& Params)
{
	FString PluginName;
	FString AssetClassPath;
	FString InputDirRel = TEXT("Model");

	const bool bOverwrite = FParse::Param(*Params, TEXT("Overwrite"));
	const bool bDryRun    = FParse::Param(*Params, TEXT("DryRun"));

	FParse::Value(*Params, TEXT("Plugin="),     PluginName);
	FParse::Value(*Params, TEXT("AssetClass="), AssetClassPath);
	FParse::Value(*Params, TEXT("InputDir="),   InputDirRel);

	if (PluginName.IsEmpty() || AssetClassPath.IsEmpty())
	{
		UE_LOG(LogTemp, Error,
			TEXT("Usage: -run=CFGenerateModelAssets -Plugin=<PluginName> -AssetClass=/Script/Module.Class ")
			TEXT("[-Overwrite] [-DryRun] [-InputDir=Model]"));
		return 1;
	}

	// Resolve the plugin we’re targeting
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Plugin '%s' not found."), *PluginName);
		return 1;
	}

	// Resolve model asset class (must derive from UCFModelAsset)
	UClass* AssetClass = nullptr;
	if (!LoadClassFromPath(AssetClassPath, AssetClass))
	{
		return 1;
	}
	if (!AssetClass->IsChildOf(UCFModelAsset::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("AssetClass '%s' must derive from UCFModelAsset."), *AssetClassPath);
		return 1;
	}

	// Scan <PluginRoot>/<InputDirRel> for *.json
	const FString BaseDir = Plugin->GetBaseDir(); // <PluginRoot>
	const FString JsonDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(BaseDir, InputDirRel));

	TArray<FString> JsonFiles;
	IFileManager::Get().FindFilesRecursive(JsonFiles, *JsonDir, TEXT("*.json"), /*Files*/true, /*Dirs*/false);

	if (JsonFiles.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No JSON files found under: %s"), *JsonDir);
		return 0;
	}

	UE_LOG(LogTemp, Display, TEXT("Found %d JSON file(s) under %s"), JsonFiles.Num(), *JsonDir);

	int32 Created = 0, Updated = 0, Skipped = 0, Failed = 0;

	for (const FString& JsonPathAbs : JsonFiles)
	{
		const FString Stem        = FPaths::GetBaseFilename(JsonPathAbs); // "CEModelAsset_Seed"
		const FString PackagePath = FString::Printf(TEXT("/%s/Model/%s"), *PluginName, *Stem);

		// Read JSON
		FString JsonText;
		if (!FFileHelper::LoadFileToString(JsonText, *JsonPathAbs))
		{
			UE_LOG(LogTemp, Error, TEXT("Read failed: %s"), *JsonPathAbs);
			++Failed;
			continue;
		}

		// Create or find package and asset
		UPackage* Package = CreatePackage(*PackagePath);

		// Look up an existing asset with that name & class in the package (if any)
		UObject* ExistingObj = StaticFindObjectFast(AssetClass, Package, FName(*Stem));
		UCFModelAsset* Asset = Cast<UCFModelAsset>(ExistingObj);

		const bool bIsNew = (Asset == nullptr);
		if (bIsNew)
		{
			if (bDryRun)
			{
				UE_LOG(LogTemp, Display, TEXT("[DRY] Would create asset %s (%s)"), *PackagePath, *AssetClass->GetName());
				++Created;
				continue;
			}

			Asset = NewObject<UCFModelAsset>(Package, AssetClass, FName(*Stem), RF_Public | RF_Standalone);
			FAssetRegistryModule::AssetCreated(Asset);
		}
		else if (!bOverwrite)
		{
			UE_LOG(LogTemp, Display, TEXT("Skip (exists, no -Overwrite): %s"), *PackagePath);
			++Skipped;
			continue;
		}

		// Import JSON into the asset’s model struct (uses asset's public helper)
		{
			FString Err;
			if (!Asset->ApplyJsonString(JsonText, Err))
			{
				UE_LOG(LogTemp, Error, TEXT("JSON import failed for %s: %s"), *PackagePath, *Err);
				++Failed;
				continue;
			}
		}

		Asset->MarkPackageDirty();

		if (bDryRun)
		{
			UE_LOG(LogTemp, Display, TEXT("[DRY] Would save: %s"), *PackagePath);
			(bIsNew ? ++Created : ++Updated);
			continue;
		}

		// Save to <PluginRoot>/Content/Model/<Stem>.uasset
		const FString PackageFilename = FPackageName::LongPackageNameToFilename(
			PackagePath, FPackageName::GetAssetPackageExtension());

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.SaveFlags     = SAVE_None;
		SaveArgs.Error         = GError;

		const bool bSaved = UPackage::SavePackage(
			Package,      // InOuter
			Asset,        // InAsset
			*PackageFilename,
			SaveArgs
		);

		if (!bSaved)
		{
			UE_LOG(LogTemp, Error, TEXT("Save failed: %s"), *PackageFilename);
			++Failed;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s: %s"),
				(bIsNew ? TEXT("Created") : TEXT("Updated")), *PackageFilename);
			(bIsNew ? ++Created : ++Updated);
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Done. Created:%d Updated:%d Skipped:%d Failed:%d"),
		Created, Updated, Skipped, Failed);

	return (Failed == 0) ? 0 : 1;
}