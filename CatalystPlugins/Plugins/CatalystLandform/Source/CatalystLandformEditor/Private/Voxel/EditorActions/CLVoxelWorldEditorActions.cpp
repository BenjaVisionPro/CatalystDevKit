#include "Voxel/EditorActions/CLVoxelWorldEditorActions.h"

#include "VoxelWorld.h"
#include "Voxel/Components/CLVoxelWorldComponent.h"
#include "Model/CLModelAsset.h"

// Editor framework
#include "ToolMenus.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"   // GEditor, GetSelectedActorIterator (forward decl)
#include "Selection.h"             // FSelectionIterator concrete definition
#include "LevelEditor.h"
#include "ScopedTransaction.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "CLVoxelWorldEditorActions"

static const FName CLSectionName = TEXT("CatalystLandform");
static const FName CLEntryName   = TEXT("EnableCatalystLandform");

namespace
{
	static UCLModelAsset* GetFirstSelectedCLModelAssetInCB()
	{
		FContentBrowserModule& CB = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		TArray<FAssetData> Selected; 
		CB.Get().GetSelectedAssets(Selected);
		for (const FAssetData& Asset : Selected)
		{
			if (Asset.GetClass() && Asset.GetClass()->IsChildOf(UCLModelAsset::StaticClass()))
			{
				return Cast<UCLModelAsset>(Asset.GetAsset());
			}
		}
		return nullptr;
	}
}

void CLVoxelWorldEditorActions::RegisterMenus()
{
	if (!UToolMenus::IsToolMenuUIEnabled())
	{
		return;
	}

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.ActorContextMenu");
	FToolMenuSection& Section = Menu->AddSection(CLSectionName, LOCTEXT("CL_Section", "Catalyst Landform"));

	Section.AddMenuEntry(
		CLEntryName,
		LOCTEXT("Enable_Label", "Enable Catalyst Landform"),
		LOCTEXT("Enable_Tip",   "Add CLVoxelWorldComponent to the selected VoxelWorld(s). If a CLModelAsset is selected in the Content Browser, it will be assigned."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateStatic(&CLVoxelWorldEditorActions::EnableCatalystLandform_OnSelectedWorlds),
			FCanExecuteAction::CreateLambda([]()
			{
				if (!GEditor) return false;
				if (USelection* Sel = GEditor->GetSelectedActors())
				{
					for (FSelectionIterator It(*Sel); It; ++It)
					{
						if (Cast<AVoxelWorld>(*It)) return true;
					}
				}
				return false;
			})
		)
	);
}

void CLVoxelWorldEditorActions::UnregisterMenus()
{
	if (UToolMenus::IsToolMenuUIEnabled())
	{
		UToolMenus::Get()->RemoveEntry("LevelEditor.ActorContextMenu", CLSectionName, CLEntryName);
	}
}

UCLVoxelWorldComponent* CLVoxelWorldEditorActions::AddComponentIfMissing(AVoxelWorld& World, UCLModelAsset* OptionalModelAsset, bool bMarkDirty)
{
	if (UCLVoxelWorldComponent* Existing = World.FindComponentByClass<UCLVoxelWorldComponent>())
	{
		// Assign only if not already set
		if (OptionalModelAsset && !Existing->CLModelAsset.IsValid())
		{
			Existing->Modify();
			Existing->CLModelAsset = OptionalModelAsset; // TSoftObjectPtr accepts raw*
		}
		return Existing;
	}

	const FScopedTransaction Tx(LOCTEXT("Tx_AddCLComp", "Add Catalyst Landform Component"));
	World.Modify();

	UCLVoxelWorldComponent* NewComp = NewObject<UCLVoxelWorldComponent>(&World, UCLVoxelWorldComponent::StaticClass(), NAME_None, RF_Transactional);
	check(NewComp);

	NewComp->RegisterComponent();
	World.AddInstanceComponent(NewComp);

	if (OptionalModelAsset)
	{
		NewComp->Modify();
		NewComp->CLModelAsset = OptionalModelAsset;
	}

	if (bMarkDirty)
	{
		World.MarkPackageDirty();
	}
	return NewComp;
}

void CLVoxelWorldEditorActions::EnableCatalystLandform_OnSelectedWorlds()
{
	if (!GEditor) return;

	UCLModelAsset* PickedModel = GetFirstSelectedCLModelAssetInCB();
	int32 NumAffected = 0;

	if (USelection* Sel = GEditor->GetSelectedActors())
	{
		for (FSelectionIterator It(*Sel); It; ++It)
		{
			if (AVoxelWorld* World = Cast<AVoxelWorld>(*It))
			{
				AddComponentIfMissing(*World, PickedModel, /*bMarkDirty*/true);
				++NumAffected;
			}
		}
	}

	FNotificationInfo Info(
		NumAffected > 0
		? FText::Format(LOCTEXT("AddedToWorlds", "Catalyst Landform enabled on {0} world(s)"), FText::AsNumber(NumAffected))
		: LOCTEXT("NoWorldSelected", "Select at least one VoxelWorld")
	);
	Info.ExpireDuration = 2.0f;
	FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE