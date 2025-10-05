// ============================================
// Catalyst Foundation — Generate Model Assets (private)
// ============================================

#include "Commandlets/CFGenerateModelAssetsCommandlet.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IPluginManager.h"
#include "Log/CFLog.h"
#define CF_LOG_DEFAULT_CATEGORY LogCatalystFoundationEditor
#include "Log/CFLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Model/CFModelAsset.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "HAL/FileManager.h"

namespace
{
	// Load a UClass from a path like /Script/Module.ClassName
	bool LoadClassFromPath(const FString& ClassPath, UClass*& OutClass)
	{
		OutClass = nullptr;
		if (ClassPath.IsEmpty()) return false;

		UClass* C = StaticLoadClass(UObject::StaticClass(), /*InOuter*/nullptr, *ClassPath);
		if (!C)
		{
			CF_ERR(TEXT("Could not load class from '%s'."), *ClassPath);
			return false;
		}
		OutClass = C;
		return true;
	}
}

UCFGenerateModelAssetsCommandlet::UCFGenerateModelAssetsCommandlet()
{
	IsClient       = false;
	IsEditor       = true;
	LogToConsole   = true;
	ShowErrorCount = true;

	HelpDescription =
		TEXT("Generate model assets from JSON files under <PluginRoot>/Model (or -InputDir).\n")
		TEXT("-Plugin=<Name> -AssetClass=/Script/Module.Class [-Overwrite] [-DryRun] [-InputDir=Model]");
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
		CF_ERR(TEXT("Usage: -run=CFGenerateModelAssets -Plugin=<PluginName> -AssetClass=/Script/Module.Class [-Overwrite] [-DryRun] [-InputDir=Model]"));
		return 1;
	}

	// Resolve plugin
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);
	if (!Plugin.IsValid())
	{
		CF_ERR(TEXT("Plugin '%s' not found."), *PluginName);
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
		CF_ERR(TEXT("AssetClass '%s' must derive from UCFModelAsset."), *AssetClassPath);
		return 1;
	}

	// Scan <PluginRoot>/<InputDirRel> for *.json
	const FString BaseDir = Plugin->GetBaseDir(); // <PluginRoot>
	const FString JsonDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(BaseDir, InputDirRel));

	TArray<FString> JsonFiles;
	IFileManager::Get().FindFilesRecursive(JsonFiles, *JsonDir, TEXT("*.json"), /*Files*/true, /*Dirs*/false);

	if (JsonFiles.Num() == 0)
	{
		CF_WARN(TEXT("No JSON files found under: %s"), *JsonDir);
		return 0;
	}

	CF_INFO(TEXT("Found %d JSON file(s) under %s"), JsonFiles.Num(), *JsonDir);

	int32 Created = 0, Updated = 0, Skipped = 0, Failed = 0;

	for (const FString& JsonPathAbs : JsonFiles)
	{
		const FString Stem        = FPaths::GetBaseFilename(JsonPathAbs);
		const FString PackagePath = FString::Printf(TEXT("/%s/Model/%s"), *PluginName, *Stem);

		// Read JSON
		FString JsonText;
		if (!FFileHelper::LoadFileToString(JsonText, *JsonPathAbs))
		{
			CF_ERR(TEXT("Read failed: %s"), *JsonPathAbs);
			++Failed;
			continue;
		}

		// Create or find package and asset
		UPackage* Package = CreatePackage(*PackagePath);

		UObject* ExistingObj = StaticFindObjectFast(AssetClass, Package, FName(*Stem));
		UCFModelAsset* Asset = Cast<UCFModelAsset>(ExistingObj);

		const bool bIsNew = (Asset == nullptr);
		if (bIsNew)
		{
			if (bDryRun)
			{
				CF_INFO(TEXT("[DRY] Would create asset %s (%s)"), *PackagePath, *AssetClass->GetName());
				++Created;
				continue;
			}

			Asset = NewObject<UCFModelAsset>(Package, AssetClass, FName(*Stem), RF_Public | RF_Standalone);
			FAssetRegistryModule::AssetCreated(Asset);
		}
		else if (!bOverwrite)
		{
			CF_INFO(TEXT("Skip (exists, no -Overwrite): %s"), *PackagePath);
			++Skipped;
			continue;
		}

		// Import JSON into the asset’s model struct
		{
			FString Err;
			if (!Asset->ApplyJsonString(JsonText, Err))
			{
				CF_ERR(TEXT("JSON import failed for %s: %s"), *PackagePath, *Err);
				++Failed;
				continue;
			}
		}

		// Refresh version/provenance metadata before saving
		Asset->UpdateVersionMetadata();
		Asset->MarkPackageDirty();

		if (bDryRun)
		{
			CF_INFO(TEXT("[DRY] Would save: %s"), *PackagePath);
			(bIsNew ? ++Created : ++Updated);
			continue;
		}

		// Save to Content path with ATOMIC write
		const FString FinalFilename = FPackageName::LongPackageNameToFilename(
			PackagePath, FPackageName::GetAssetPackageExtension());

		const FString TempFilename  = FinalFilename + TEXT(".tmp");

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.SaveFlags     = SAVE_None;
		SaveArgs.Error         = GError;

		// 1) Save to TEMP
		const bool bSavedTemp = UPackage::SavePackage(
			Package,
			Asset,
			*TempFilename,
			SaveArgs
		);

		if (!bSavedTemp)
		{
			CF_ERR(TEXT("Temp save failed: %s"), *TempFilename);
			++Failed;
			continue;
		}

		// 2) Atomic move temp -> final
		const bool bMoved = IFileManager::Get().Move(*FinalFilename, *TempFilename, /*Replace*/true, /*EvenIfReadOnly*/false, /*Attributes*/false, /*bDoNotRetryOrError*/true);
		if (!bMoved)
		{
			// Clean temp if move failed
			IFileManager::Get().Delete(*TempFilename, /*RequireExists*/false, /*EvenReadOnly*/true);
			CF_ERR(TEXT("Atomic move failed: %s -> %s"), *TempFilename, *FinalFilename);
			++Failed;
			continue;
		}

		CF_INFO(TEXT("%s: %s"), (bIsNew ? TEXT("Created") : TEXT("Updated")), *FinalFilename);
		(bIsNew ? ++Created : ++Updated);
	}

	CF_INFO(TEXT("Done. Created:%d Updated:%d Skipped:%d Failed:%d"), Created, Updated, Skipped, Failed);
	return (Failed == 0) ? 0 : 1;
}