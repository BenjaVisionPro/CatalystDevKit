#include "Toolkits/CFModelEditorToolkit.h"

#include "CFEditorModule.h"
#include "Model/CFModelAsset.h"

// Runtime model service (kept out of the public header to avoid coupling)
#include "Services/CFAbstractModelService.h"

// Validation surface (editor-safe)
#include "Validation/CFValidatable.h"
#include "Validation/CFValidationTypes.h"

// Our widgets
#include "Widgets/SCFValidationPanel.h"
#include "Widgets/SCFVersionStatusWidget.h"

#include "Engine/GameInstance.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h" // SVerticalBox
#include "Widgets/Text/STextBlock.h"
#include "Styling/AppStyle.h"

// NEW: menu/toolbar + notifications
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Commands/UIAction.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#define LOCTEXT_NAMESPACE "FCFModelEditorToolkit"

const FName FCFModelEditorToolkit::DetailsTabId    = TEXT("CFModelEditorToolkit_Details");
const FName FCFModelEditorToolkit::ValidationTabId = TEXT("CFModelEditorToolkit_Validation");

FCFModelEditorToolkit::FCFModelEditorToolkit() = default;

FCFModelEditorToolkit::~FCFModelEditorToolkit()
{
	UnbindRuntimeDelegates();
}

// --- helpers (local) ---
namespace
{
	static void CF_ShowToast(const FText& Message, SNotificationItem::ECompletionState State)
	{
		FNotificationInfo Info(Message);
		Info.bUseLargeFont = false;
		Info.bFireAndForget = true;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 2.5f;

		auto Item = FSlateNotificationManager::Get().AddNotification(Info);
		if (Item.IsValid())
		{
			Item->SetCompletionState(State);
		}
	}
}

void FCFModelEditorToolkit::InitModelEditor(
	UCFModelAsset* InAsset,
	EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	check(InAsset);
	EditingAsset = InAsset;

	BuildDetailsPanel();

	// Layout: Details (open), Validation (open by default)
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("CFModelEditorToolkit_Layout_v3")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Horizontal)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.7f)
			->AddTab(DetailsTabId, ETabState::OpenedTab)
			->SetForegroundTab(DetailsTabId)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.3f)
			->AddTab(ValidationTabId, ETabState::OpenedTab)
		)
	);

	// --- JSON actions (menu & toolbar) ---
	{
		// Menu extender
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension(
			"FileLoadAndSave",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Menu)
			{
				Menu.BeginSection("CFModelJson", LOCTEXT("CFModelJsonSection", "Model JSON"));
				{
					Menu.AddMenuEntry(
						LOCTEXT("ExportJsonLabel", "Export as JSON"),
						LOCTEXT("ExportJsonTip", "Export the current model to Saved/<Plugin>/Model.json"),
						FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save"),
						FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleExportJson))
					);

					Menu.AddMenuEntry(
						LOCTEXT("ReloadJsonLabel", "Reload from JSON"),
						LOCTEXT("ReloadJsonTip", "Reload the model from Saved/<Plugin>/Model.json"),
						FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Refresh"),
						FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleReloadJson))
					);
				}
				Menu.EndSection();
			})
		);
		AddMenuExtender(MenuExtender);

		// Toolbar extender (moved BEFORE InitAssetEditor)
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());
		ToolbarExtender->AddToolBarExtension(
			"Asset",
			EExtensionHook::After,
			nullptr,
			FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
			{
				Builder.AddToolBarButton(
					FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleExportJson)),
					NAME_None,
					LOCTEXT("ExportJson_TB", "Export JSON"),
					LOCTEXT("ExportJson_TB_Tip", "Export to Saved/<Plugin>/Model.json"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save")
				);

				Builder.AddToolBarButton(
					FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleReloadJson)),
					NAME_None,
					LOCTEXT("ReloadJson_TB", "Reload JSON"),
					LOCTEXT("ReloadJson_TB_Tip", "Reload from Saved/<Plugin>/Model.json"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Refresh")
				);
			})
		);
		AddToolbarExtender(ToolbarExtender);
	}
	// --- /JSON actions ---

	// Initialize base asset editor (now AFTER extenders are registered)
	InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		true,   // bCreateDefaultStandaloneMenu
		true,   // bCreateDefaultToolbar
		EditingAsset
	);

	// Attempt to bind to the runtime model service if we're in PIE/Game world
	TryBindRuntimeService();

	// Initial UI pass
	RefreshAllUI(EditingAsset, /*bIsReload*/false);
}

void FCFModelEditorToolkit::BuildDetailsPanel()
{
	FPropertyEditorModule& PEM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bUpdatesFromSelection = false;
	Args.bLockable = false;
	Args.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	DetailsView = PEM.CreateDetailView(Args);
	DetailsView->SetObject(EditingAsset.Get());
}

FName FCFModelEditorToolkit::GetToolkitFName() const
{
	return TEXT("CFModelEditorToolkit");
}

FText FCFModelEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("ToolkitName", "Catalyst Model");
}

FString FCFModelEditorToolkit::GetWorldCentricTabPrefix() const
{
	return TEXT("CatalystModel");
}

FLinearColor FCFModelEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.25f, 0.5f, 1.f, 0.5f);
}

void FCFModelEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(
		DetailsTabId,
		FOnSpawnTab::CreateSP(this, &FCFModelEditorToolkit::SpawnDetailsTab))
		.SetDisplayName(LOCTEXT("DetailsTabName", "Details"))
		.SetTooltipText(LOCTEXT("DetailsTabTooltip", "Edit model properties"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(
		ValidationTabId,
		FOnSpawnTab::CreateSP(this, &FCFModelEditorToolkit::SpawnValidationTab))
		.SetDisplayName(LOCTEXT("ValidationTabName", "Validation"))
		.SetTooltipText(LOCTEXT("ValidationTabTooltip", "Validation and diagnostics"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "DeveloperTools.TabIcon"));
}

void FCFModelEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(DetailsTabId);
	InTabManager->UnregisterTabSpawner(ValidationTabId);

	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

TSharedRef<SDockTab> FCFModelEditorToolkit::SpawnDetailsTab(const FSpawnTabArgs& Args)
{
	check(DetailsView.IsValid());

	return SNew(SDockTab)
		.Label(LOCTEXT("DetailsTabLabel", "Details"))
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FCFModelEditorToolkit::SpawnValidationTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> Tab =
		SNew(SDockTab)
		.Label(LOCTEXT("ValidationTabLabel", "Validation"))
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			.Padding(4)
			[
				SNew(SVerticalBox)

				// Version banner
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(2)
				[
					SAssignNew(VersionBanner, SCFVersionStatusWidget, EditingAsset.Get())
				]

				// Validation list
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
				.Padding(2)
				[
					SAssignNew(ValidationPanel, SCFValidationPanel)
				]
			]
		];

	if (VersionBanner.IsValid())
	{
		VersionBanner->Refresh();
	}
	if (ValidationPanel.IsValid())
	{
		ValidationPanel->SetAsset(EditingAsset.Get());
		ValidationPanel->Refresh();
	}

	return Tab;
}

// -------- Runtime service orchestration --------

void FCFModelEditorToolkit::TryBindRuntimeService()
{
	UWorld* TargetWorld = nullptr;

#if WITH_EDITOR
	if (GEditor)
	{
		for (const FWorldContext& Ctx : GEditor->GetWorldContexts())
		{
			if (Ctx.WorldType == EWorldType::PIE && Ctx.World())
			{
				TargetWorld = Ctx.World();
				break;
			}
		}
		if (!TargetWorld && GEditor->GetPIEWorldContext())
		{
			TargetWorld = GEditor->GetPIEWorldContext()->World();
		}
	}
#endif

	if (!TargetWorld && GEngine)
	{
		for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
		{
			if ((Ctx.WorldType == EWorldType::PIE || Ctx.WorldType == EWorldType::Game) && Ctx.World())
			{
				TargetWorld = Ctx.World();
				break;
			}
		}
	}

	if (!TargetWorld)
	{
		return;
	}

	UGameInstance* GI = TargetWorld->GetGameInstance();
	if (!GI)
	{
		return;
	}

	UGameInstanceSubsystem* Base = GI->GetSubsystemBase(UCFAbstractModelService::StaticClass());
	if (Base && Base->IsA(UCFAbstractModelService::StaticClass()))
	{
		RuntimeService = Cast<UCFAbstractModelService>(Base);
		BindRuntimeDelegates();
	}
}

void FCFModelEditorToolkit::BindRuntimeDelegates()
{
	if (!RuntimeService.IsValid())
		return;

	RuntimeService->OnModelReady.AddRaw(this, &FCFModelEditorToolkit::HandleModelReady);
	RuntimeService->OnModelReloaded.AddRaw(this, &FCFModelEditorToolkit::HandleModelReloaded);
	RuntimeService->OnModelUpdated.AddRaw(this, &FCFModelEditorToolkit::HandleModelUpdated);
	RuntimeService->OnModelError.AddRaw(this, &FCFModelEditorToolkit::HandleModelError);
	RuntimeService->OnModelErrorEx.AddRaw(this, &FCFModelEditorToolkit::HandleModelErrorEx);
}

void FCFModelEditorToolkit::UnbindRuntimeDelegates()
{
	if (!RuntimeService.IsValid())
		return;

	RuntimeService->OnModelReady.RemoveAll(this);
	RuntimeService->OnModelReloaded.RemoveAll(this);
	RuntimeService->OnModelUpdated.RemoveAll(this);
	RuntimeService->OnModelError.RemoveAll(this);
	RuntimeService->OnModelErrorEx.RemoveAll(this);
}

void FCFModelEditorToolkit::RefreshAllUI(UCFModelAsset* LiveModel, bool bIsReload)
{
	UCFModelAsset* Target = LiveModel ? LiveModel : EditingAsset.Get();

	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(Target);
	}

	if (VersionBanner.IsValid())
	{
		VersionBanner->SetAsset(Target);
		VersionBanner->Refresh();
	}

	if (ValidationPanel.IsValid())
	{
		ValidationPanel->SetAsset(Target);
		ValidationPanel->Refresh();
	}
}

// ---- JSON actions ----

void FCFModelEditorToolkit::HandleExportJson()
{
	if (!EditingAsset)
	{
		CF_ShowToast(LOCTEXT("Export_NoAsset", "No asset to export."), SNotificationItem::CS_Fail);
		return;
	}

	FString Error;
	if (EditingAsset->SaveToDiskJson(Error))
	{
		CF_ShowToast(LOCTEXT("Export_Success", "Exported JSON to Saved/<Plugin>/Model.json."), SNotificationItem::CS_Success);
	}
	else
	{
		CF_ShowToast(FText::Format(LOCTEXT("Export_FailFmt", "Export failed: {0}"), FText::FromString(Error)), SNotificationItem::CS_Fail);
	}
}

void FCFModelEditorToolkit::HandleReloadJson()
{
	if (!EditingAsset)
	{
		CF_ShowToast(LOCTEXT("Reload_NoAsset", "No asset to reload."), SNotificationItem::CS_Fail);
		return;
	}

	FString Error;
	if (EditingAsset->TryLoadFromDiskJson(Error))
	{
		RefreshAllUI(EditingAsset.Get(), /*bIsReload*/true);
		CF_ShowToast(LOCTEXT("Reload_Success", "Reloaded JSON from Saved/<Plugin>/Model.json."), SNotificationItem::CS_Success);
	}
	else
	{
		CF_ShowToast(FText::Format(LOCTEXT("Reload_FailFmt", "Reload failed: {0}"), FText::FromString(Error)), SNotificationItem::CS_Fail);
	}
}

// ---- Delegate handlers ----

void FCFModelEditorToolkit::HandleModelReady(UCFModelAsset* LiveModel)
{
	RefreshAllUI(LiveModel, false);
}

void FCFModelEditorToolkit::HandleModelReloaded(UCFModelAsset* LiveModel)
{
	RefreshAllUI(LiveModel, true);
}

void FCFModelEditorToolkit::HandleModelUpdated()
{
	RefreshAllUI(RuntimeService.IsValid() ? RuntimeService->GetMutable() : EditingAsset.Get(), true);
}

void FCFModelEditorToolkit::HandleModelError(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("ModelService Error: %s"), *Message);
	RefreshAllUI(RuntimeService.IsValid() ? RuntimeService->GetMutable() : EditingAsset.Get(), true);
}

void FCFModelEditorToolkit::HandleModelErrorEx(const FCFModelError& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("ModelService ErrorEx: Code=%d Msg=%s Ctx=%s"),
		(int32)Error.Code, *Error.Message, *Error.Context);
	RefreshAllUI(RuntimeService.IsValid() ? RuntimeService->GetMutable() : EditingAsset.Get(), true);
}

#undef LOCTEXT_NAMESPACE