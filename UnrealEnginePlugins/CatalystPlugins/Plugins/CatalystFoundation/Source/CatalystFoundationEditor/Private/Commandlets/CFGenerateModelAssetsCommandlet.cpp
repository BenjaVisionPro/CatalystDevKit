// ============================================
// Catalyst Foundation — Generate Model Assets (Commandlet)
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
#include "Misc/DateTime.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

#include "Log/CFLog.h"     // CF_INFO / CF_ERR etc.
#include "CatalystFoundation.h" // ensures DECLARE_LOG_CATEGORY_EXTERN is visible

namespace CFGenerate
{
	static FString NowUtcStamp()
	{
		// e.g. 2025-10-05T14-07-22Z
		const FDateTime Utc = FDateTime::UtcNow();
		return Utc.ToString(TEXT("%Y-%m-%dT%H-%M-%SZ"));
	}

	static FString ReportDirForPlugin(const FString& PluginName)
	{
		// Saved/<Plugin>/Reports
		return FPaths::Combine(FPaths::ProjectSavedDir(), PluginName, TEXT("Reports"));
	}

	static FString ReportPath(const FString& PluginName)
	{
		return FPaths::Combine(ReportDirForPlugin(PluginName),
			FString::Printf(TEXT("CF_GenerateReport_%s.json"), *NowUtcStamp()));
	}
}

UCFGenerateModelAssetsCommandlet::UCFGenerateModelAssetsCommandlet()
{
	IsClient       = false;
	IsEditor       = true;
	LogToConsole   = true;
	ShowErrorCount = true;

	HelpDescription =
		TEXT("Generate model assets from JSON files under <PluginRoot>/<InputDir> (default: Model). ") \
		TEXT("Writes a CI-friendly JSON report under Saved/<Plugin>/Reports.\n") \
		TEXT("Args: -Plugin=<Name> -AssetClass=/Script/Module.Class [-InputDir=Model] [-Overwrite] [-DryRun] [-FailFast]");
}

// Load a UClass from a soft path like /Script/Module.ClassName
static bool LoadClassFromPath(const FString& ClassPath, UClass*& OutClass)
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

int32 UCFGenerateModelAssetsCommandlet::Main(const FString& Params)
{
	// ----------------------------
	// Parse args
	// ----------------------------
	FString PluginName;
	FString AssetClassPath;
	FString InputDirRel = TEXT("Model");

	const bool bOverwrite = FParse::Param(*Params, TEXT("Overwrite"));
	const bool bDryRun    = FParse::Param(*Params, TEXT("DryRun"));
	const bool bFailFast  = FParse::Param(*Params, TEXT("FailFast"));

	FParse::Value(*Params, TEXT("Plugin="),     PluginName);
	FParse::Value(*Params, TEXT("AssetClass="), AssetClassPath);
	FParse::Value(*Params, TEXT("InputDir="),   InputDirRel);

	if (PluginName.IsEmpty() || AssetClassPath.IsEmpty())
	{
		CF_ERR(TEXT("Usage: -run=CFGenerateModelAssets -Plugin=<PluginName> -AssetClass=/Script/Module.Class [-Overwrite] [-DryRun] [-FailFast] [-InputDir=Model]"));
		return 1;
	}

	// ----------------------------
	// Resolve plugin + class
	// ----------------------------
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);
	if (!Plugin.IsValid())
	{
		CF_ERR(TEXT("Plugin '%s' not found."), *PluginName);
		return 1;
	}

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

	// ----------------------------
	// Find JSON files
	// ----------------------------
	const FString BaseDir = Plugin->GetBaseDir(); // <PluginRoot>
	const FString JsonDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(BaseDir, InputDirRel));

	TArray<FString> JsonFiles;
	IFileManager::Get().FindFilesRecursive(JsonFiles, *JsonDir, TEXT("*.json"), /*Files*/true, /*Dirs*/false);

	if (JsonFiles.Num() == 0)
	{
		CF_WARN(TEXT("No JSON files found under: %s"), *JsonDir);
		// Still write an empty report so CI has an artifact to read
	}

	CF_INFO(TEXT("Found %d JSON file(s) under %s"), JsonFiles.Num(), *JsonDir);

	// ----------------------------
	// Per-run report data
	// ----------------------------
	int32 Created = 0, Updated = 0, Skipped = 0, Failed = 0;

	TArray<TSharedPtr<FJsonValue>> Items;

	auto AddItem = [&](const FString& JsonPathAbs, const FString& AssetLongPath, const FString& Result, const TArray<FString>& Warnings)
	{
		TSharedPtr<FJsonObject> Item = MakeShared<FJsonObject>();
		Item->SetStringField(TEXT("json"),  JsonPathAbs);
		Item->SetStringField(TEXT("asset"), AssetLongPath);
		Item->SetStringField(TEXT("result"), Result);
		if (Warnings.Num() > 0)
		{
			TArray<TSharedPtr<FJsonValue>> WarnVals;
			for (const FString& W : Warnings)
			{
				WarnVals.Add(MakeShared<FJsonValueString>(W));
			}
			Item->SetArrayField(TEXT("warnings"), WarnVals);
		}
		Items.Add(MakeShared<FJsonValueObject>(Item));
	};

	// ----------------------------
	// Process each JSON file
	// ----------------------------
	for (const FString& JsonPathAbs : JsonFiles)
	{
		const FString Stem        = FPaths::GetBaseFilename(JsonPathAbs);
		const FString PackagePath = FString::Printf(TEXT("/%s/Model/%s"), *PluginName, *Stem);

		// Read file
		FString JsonText;
		if (!FFileHelper::LoadFileToString(JsonText, *JsonPathAbs))
		{
			CF_ERR(TEXT("Read failed: %s"), *JsonPathAbs);
			AddItem(JsonPathAbs, PackagePath, TEXT("Failed"), {});
			++Failed;
			if (bFailFast) break;
			continue;
		}

		// Create/find package + asset
		UPackage* Package = CreatePackage(*PackagePath);
		UObject* ExistingObj = StaticFindObjectFast(AssetClass, Package, FName(*Stem));
		UCFModelAsset* Asset = Cast<UCFModelAsset>(ExistingObj);
		const bool bIsNew = (Asset == nullptr);

		if (bIsNew && bDryRun)
		{
			CF_INFO(TEXT("[DRY] Would create asset %s (%s)"), *PackagePath, *AssetClass->GetName());
			AddItem(JsonPathAbs, PackagePath, TEXT("WouldCreate"), {});
			++Created;
			continue;
		}
		if (!bIsNew && !bOverwrite)
		{
			CF_INFO(TEXT("Skip (exists, no -Overwrite): %s"), *PackagePath);
			AddItem(JsonPathAbs, PackagePath, TEXT("Skipped"), {});
			++Skipped;
			continue;
		}

		if (bIsNew)
		{
			Asset = NewObject<UCFModelAsset>(Package, AssetClass, FName(*Stem), RF_Public | RF_Standalone);
			FAssetRegistryModule::AssetCreated(Asset);
		}

		// Apply JSON
		{
			FString Err;
			if (!Asset->ApplyJsonString(JsonText, Err))
			{
				CF_ERR(TEXT("JSON import failed for %s: %s"), *PackagePath, *Err);
				AddItem(JsonPathAbs, PackagePath, TEXT("Failed"), { Err });
				++Failed;
				if (bFailFast) break;
				continue;
			}
		}

		Asset->MarkPackageDirty();

		if (bDryRun)
		{
			CF_INFO(TEXT("[DRY] Would save: %s"), *PackagePath);
			AddItem(JsonPathAbs, PackagePath, bIsNew ? TEXT("WouldCreate") : TEXT("WouldUpdate"), {});
			(bIsNew ? ++Created : ++Updated);
			continue;
		}

		// Save package (atomic: write to tmp then move)
		const FString PackageFilename = FPackageName::LongPackageNameToFilename(
			PackagePath, FPackageName::GetAssetPackageExtension());

		const FString TmpFilename = PackageFilename + TEXT(".tmp");

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.SaveFlags     = SAVE_None;
		SaveArgs.Error         = GError;

		const bool bSavedTmp = UPackage::SavePackage(
			Package,      // InOuter
			Asset,        // InAsset
			*TmpFilename,
			SaveArgs
		);

		if (!bSavedTmp)
		{
			CF_ERR(TEXT("Save (tmp) failed: %s"), *TmpFilename);
			AddItem(JsonPathAbs, PackagePath, TEXT("Failed"), { TEXT("Temp save failed") });
			++Failed;
			if (bFailFast) break;
			continue;
		}

		// Move tmp -> final (replace)
		const bool bMoved = IFileManager::Get().Move(*PackageFilename, *TmpFilename, /*Replace*/true, /*EvenIfReadOnly*/true, /*Attributes*/false, /*DoNotRetry*/true);
		if (!bMoved)
		{
			// Cleanup tmp on failure
			IFileManager::Get().Delete(*TmpFilename);
			CF_ERR(TEXT("Atomic move failed: %s -> %s"), *TmpFilename, *PackageFilename);
			AddItem(JsonPathAbs, PackagePath, TEXT("Failed"), { TEXT("Atomic move failed") });
			++Failed;
			if (bFailFast) break;
			continue;
		}

		CF_INFO(TEXT("%s: %s"), bIsNew ? TEXT("Created") : TEXT("Updated"), *PackageFilename);
		AddItem(JsonPathAbs, PackagePath, bIsNew ? TEXT("Created") : TEXT("Updated"), {});
		(bIsNew ? ++Created : ++Updated);
	}

	// ----------------------------
	// Emit CI report
	// ----------------------------
	const FString ReportDir  = CFGenerate::ReportDirForPlugin(PluginName);
	IFileManager::Get().MakeDirectory(*ReportDir, /*Tree*/true);
	const FString ReportPath = CFGenerate::ReportPath(PluginName);

	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("plugin"), PluginName);
	Root->SetNumberField(TEXT("created"), Created);
	Root->SetNumberField(TEXT("updated"), Updated);
	Root->SetNumberField(TEXT("skipped"), Skipped);
	Root->SetNumberField(TEXT("failed"),  Failed);
	Root->SetArrayField(TEXT("items"), Items);

	FString ReportText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ReportText);
		FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	}

	// Atomic write of the report
	const FString TmpReport = ReportPath + TEXT(".tmp");
	bool bReportOk = FFileHelper::SaveStringToFile(ReportText, *TmpReport);
	if (bReportOk)
	{
		bReportOk = IFileManager::Get().Move(*ReportPath, *TmpReport, /*Replace*/true, /*EvenIfReadOnly*/true, /*Attributes*/false, /*DoNotRetry*/true);
	}
	if (!bReportOk)
	{
		IFileManager::Get().Delete(*TmpReport);
		CF_ERR(TEXT("Failed to write report: %s"), *ReportPath);
	}
	else
	{
		CF_INFO(TEXT("Wrote CI report: %s"), *ReportPath);
	}

	// ----------------------------
	// Summary + exit code
	// ----------------------------
	CF_INFO(TEXT("Summary — Created:%d Updated:%d Skipped:%d Failed:%d"), Created, Updated, Skipped, Failed);

	if (Failed > 0 && bFailFast)
	{
		return 1; // fail on first error mode (already stopped early)
	}
	return (Failed == 0) ? 0 : 1;
}