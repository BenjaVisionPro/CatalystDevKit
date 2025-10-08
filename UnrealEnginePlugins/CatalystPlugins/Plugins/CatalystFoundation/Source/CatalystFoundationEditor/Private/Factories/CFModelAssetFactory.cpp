#include "Factories/CFModelAssetFactory.h"
#include "Model/CFModelAsset.h"
#include "Log/CFLog.h"

#include "EditorFramework/AssetImportData.h"   // ImportData
#include "Misc/FileHelper.h"                   // LoadFileToString
#include "Misc/Paths.h"

UCFModelAssetFactory::UCFModelAssetFactory()
{
	bCreateNew     = true;
	bEditAfterNew  = true;
	SupportedClass = nullptr; // Resolved dynamically

	CF_INFO(TEXT("[%s] ctor: bCreateNew=%d bEditAfterNew=%d"),
		*GetClass()->GetName(), (int32)bCreateNew, (int32)bEditAfterNew);
}

FText UCFModelAssetFactory::GetDisplayName() const
{
	return GetAssetMenuName();
}

FText UCFModelAssetFactory::GetToolTip() const
{
	static const FText Tip = NSLOCTEXT("CatalystFoundationEditor", "CFModelAssetFactory_Tooltip",
		"Create a new Catalyst model asset.");
	return Tip;
}

UClass* UCFModelAssetFactory::ResolveSupportedClass()
{
	UClass* Target = GetAssetClass();
	if (!ValidateSupportedClass(Target))
	{
		Target = UCFModelAsset::StaticClass();
		CF_WARN(TEXT("[%s] Invalid or null asset class; falling back to UCFModelAsset"),
			*GetClass()->GetName());
	}
	return Target;
}

bool UCFModelAssetFactory::ValidateSupportedClass(UClass* InClass) const
{
	if (!InClass)
	{
		CF_ERR(TEXT("[%s] GetAssetClass() returned null."), *GetClass()->GetName());
		return false;
	}
	if (!InClass->IsChildOf(UCFModelAsset::StaticClass()))
	{
		CF_ERR(TEXT("[%s] %s does not derive from UCFModelAsset."),
			*GetClass()->GetName(), *InClass->GetName());
		return false;
	}
	return true;
}

UObject* UCFModelAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* /*Context*/,
	FFeedbackContext* /*Warn*/)
{
	UClass* TargetClass = InClass ? InClass : ResolveSupportedClass();
	if (!ValidateSupportedClass(TargetClass))
	{
		CF_ERR(TEXT("[%s] Aborting create; invalid TargetClass."), *GetClass()->GetName());
		return nullptr;
	}

	UObject* NewAsset = NewObject<UObject>(InParent, TargetClass, Name, Flags | RF_Public | RF_Standalone);
	if (!NewAsset)
	{
		CF_ERR(TEXT("[%s] Failed to create asset %s of class %s"),
			*GetClass()->GetName(), *Name.ToString(), *TargetClass->GetName());
		return nullptr;
	}

	InitializeNewAsset(NewAsset);
	return NewAsset;
}

// ============================================================================
// FReimportHandler (UE reimport pipeline) — enables "Reimport" from JSON
// ============================================================================

bool UCFModelAssetFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	const UCFModelAsset* Model = Cast<UCFModelAsset>(Obj);
#if WITH_EDITORONLY_DATA
	if (Model && Model->ImportData)
	{
		// Only advertise reimport if we actually have a recorded source path.
		const FString Src = Model->ImportData->GetFirstFilename();
		if (!Src.IsEmpty())
		{
			OutFilenames.Add(Src);
			return true;
		}
	}
#endif
	return false;
}

void UCFModelAssetFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewPaths)
{
#if WITH_EDITORONLY_DATA
	if (UCFModelAsset* Model = Cast<UCFModelAsset>(Obj))
	{
		if (Model->ImportData && NewPaths.Num() > 0)
		{
			Model->ImportData->Update(NewPaths[0]);
			CF_INFO(TEXT("[%s] Reimport path set to: %s"), *GetClass()->GetName(), *NewPaths[0]);
		}
	}
#endif
}

EReimportResult::Type UCFModelAssetFactory::Reimport(UObject* Obj)
{
	UCFModelAsset* Model = Cast<UCFModelAsset>(Obj);
	if (!Model)
	{
		return EReimportResult::Failed;
	}

#if WITH_EDITORONLY_DATA
	if (!Model->ImportData)
	{
		CF_WARN(TEXT("[%s] Reimport aborted: no ImportData on asset."), *GetClass()->GetName());
		return EReimportResult::Failed;
	}

	const FString Src = Model->ImportData->GetFirstFilename();
	if (Src.IsEmpty())
	{
		CF_WARN(TEXT("[%s] Reimport aborted: ImportData has no source filename."), *GetClass()->GetName());
		return EReimportResult::Failed;
	}

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *Src))
	{
		CF_ERR(TEXT("[%s] Reimport failed: could not read %s"), *GetClass()->GetName(), *Src);
		return EReimportResult::Failed;
	}

	FString Error;
	if (!Model->ApplyJsonString(JsonText, Error))
	{
		CF_ERR(TEXT("[%s] Reimport failed: %s"), *GetClass()->GetName(), *Error);
		return EReimportResult::Failed;
	}

	// Nudge the editor & mark dirty so UI and assets update.
	Model->Modify();
	Model->PostEditChange();
	Model->MarkPackageDirty();

	CF_INFO(TEXT("[%s] Reimported from: %s"), *GetClass()->GetName(), *Src);
	return EReimportResult::Succeeded;
#else
	return EReimportResult::Failed;
#endif
}