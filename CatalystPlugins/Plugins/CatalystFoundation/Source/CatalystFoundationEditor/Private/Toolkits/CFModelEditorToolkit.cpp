#include "Toolkits/CFModelEditorToolkit.h"
#include "CFEditorModule.h"
#include "Model/CFModelAsset.h"
#include "Validation/CFValidatable.h"
#include "Validation/CFValidationTypes.h"
#include "Widgets/SCFValidationPanel.h"
#include "Widgets/SCFVersionStatusWidget.h"

#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/AppStyle.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#define LOCTEXT_NAMESPACE "FCFModelEditorToolkit"

const FName FCFModelEditorToolkit::DetailsTabId    = TEXT("CFModelEditorToolkit_Details");
const FName FCFModelEditorToolkit::ValidationTabId = TEXT("CFModelEditorToolkit_Validation");

FCFModelEditorToolkit::FCFModelEditorToolkit() = default;
FCFModelEditorToolkit::~FCFModelEditorToolkit() { UnbindRuntimeDelegates(); }

// --- helpers (local) ---
namespace
{
	static void CF_ShowToast(const FText& Message, SNotificationItem::ECompletionState State)
	{
		FNotificationInfo Info(Message);
		Info.bFireAndForget = true;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 2.5f;
		auto Item = FSlateNotificationManager::Get().AddNotification(Info);
		if (Item.IsValid()) Item->SetCompletionState(State);
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

	// --- Menu & toolbar (only export now) ---
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension(
			"FileLoadAndSave", EExtensionHook::After, nullptr,
			FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& Menu)
			{
				Menu.BeginSection("CFModelJson", LOCTEXT("CFModelJsonSection", "Model JSON"));
				Menu.AddMenuEntry(
					LOCTEXT("ExportJsonLabel", "Export as JSON"),
					LOCTEXT("ExportJsonTip", "Export the current model to Saved/<Plugin>/Model.json"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save"),
					FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleExportJson))
				);
				Menu.EndSection();
			})
		);
		AddMenuExtender(MenuExtender);

		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());
		ToolbarExtender->AddToolBarExtension(
			"Asset", EExtensionHook::After, nullptr,
			FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
			{
				Builder.AddToolBarButton(
					FUIAction(FExecuteAction::CreateRaw(this, &FCFModelEditorToolkit::HandleExportJson)),
					NAME_None,
					LOCTEXT("ExportJson_TB", "Export JSON"),
					LOCTEXT("ExportJson_TB_Tip", "Export to Saved/<Plugin>/Model.json"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save")
				);
			})
		);
		AddToolbarExtender(ToolbarExtender);
	}

	InitAssetEditor(
		Mode, InitToolkitHost, GetToolkitFName(),
		Layout, true, true, EditingAsset
	);

	TryBindRuntimeService();
	RefreshAllUI(EditingAsset, false);
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

FName FCFModelEditorToolkit::GetToolkitFName() const { return TEXT("CFModelEditorToolkit"); }
FText FCFModelEditorToolkit::GetBaseToolkitName() const { return LOCTEXT("ToolkitName", "Catalyst Model"); }
FString FCFModelEditorToolkit::GetWorldCentricTabPrefix() const { return TEXT("CatalystModel"); }
FLinearColor FCFModelEditorToolkit::GetWorldCentricTabColorScale() const { return FLinearColor(0.25f, 0.5f, 1.f, 0.5f); }

void FCFModelEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(DetailsTabId,
		FOnSpawnTab::CreateSP(this, &FCFModelEditorToolkit::SpawnDetailsTab))
		.SetDisplayName(LOCTEXT("DetailsTabName", "Details"))
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(ValidationTabId,
		FOnSpawnTab::CreateSP(this, &FCFModelEditorToolkit::SpawnValidationTab))
		.SetDisplayName(LOCTEXT("ValidationTabName", "Validation"))
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
	return SNew(SDockTab).Label(LOCTEXT("DetailsTabLabel", "Details"))[DetailsView.ToSharedRef()];
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
				+ SVerticalBox::Slot().AutoHeight().Padding(2)
				[
					SAssignNew(VersionBanner, SCFVersionStatusWidget, EditingAsset.Get())
				]
				+ SVerticalBox::Slot().FillHeight(1.f).Padding(2)
				[
					SAssignNew(ValidationPanel, SCFValidationPanel)
				]
			]
		];

	if (VersionBanner.IsValid()) VersionBanner->Refresh();
	if (ValidationPanel.IsValid())
	{
		ValidationPanel->SetAsset(EditingAsset.Get());
		ValidationPanel->Refresh();
	}

	return Tab;
}

void FCFModelEditorToolkit::TryBindRuntimeService()
{
#if WITH_EDITOR
	if (GEditor)
	{
		for (const FWorldContext& Ctx : GEditor->GetWorldContexts())
		{
			if (Ctx.WorldType == EWorldType::PIE && Ctx.World())
			{
				if (UGameInstance* GI = Ctx.World()->GetGameInstance())
				{
					if (UGameInstanceSubsystem* Base = GI->GetSubsystemBase(UCFAbstractModelService::StaticClass()))
					{
						RuntimeService = Cast<UCFAbstractModelService>(Base);
						BindRuntimeDelegates();
					}
				}
				break;
			}
		}
	}
#endif
}

void FCFModelEditorToolkit::BindRuntimeDelegates()
{
	if (!RuntimeService.IsValid()) return;
	RuntimeService->OnModelReady.AddRaw(this, &FCFModelEditorToolkit::HandleModelReady);
	RuntimeService->OnModelReloaded.AddRaw(this, &FCFModelEditorToolkit::HandleModelReloaded);
	RuntimeService->OnModelUpdated.AddRaw(this, &FCFModelEditorToolkit::HandleModelUpdated);
	RuntimeService->OnModelError.AddRaw(this, &FCFModelEditorToolkit::HandleModelError);
	RuntimeService->OnModelErrorEx.AddRaw(this, &FCFModelEditorToolkit::HandleModelErrorEx);
}

void FCFModelEditorToolkit::UnbindRuntimeDelegates()
{
	if (!RuntimeService.IsValid()) return;
	RuntimeService->OnModelReady.RemoveAll(this);
	RuntimeService->OnModelReloaded.RemoveAll(this);
	RuntimeService->OnModelUpdated.RemoveAll(this);
	RuntimeService->OnModelError.RemoveAll(this);
	RuntimeService->OnModelErrorEx.RemoveAll(this);
}

void FCFModelEditorToolkit::RefreshAllUI(UCFModelAsset* LiveModel, bool bIsReload)
{
	UCFModelAsset* Target = LiveModel ? LiveModel : EditingAsset.Get();
	if (DetailsView.IsValid()) DetailsView->SetObject(Target);
	if (VersionBanner.IsValid()) { VersionBanner->SetAsset(Target); VersionBanner->Refresh(); }
	if (ValidationPanel.IsValid()) { ValidationPanel->SetAsset(Target); ValidationPanel->Refresh(); }
}

// ---- Toolbar Actions ----

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

// ---- Delegate handlers ----

void FCFModelEditorToolkit::HandleModelReady(UCFModelAsset* LiveModel)      { RefreshAllUI(LiveModel, false); }
void FCFModelEditorToolkit::HandleModelReloaded(UCFModelAsset* LiveModel)   { RefreshAllUI(LiveModel, true);  }
void FCFModelEditorToolkit::HandleModelUpdated()                            { RefreshAllUI(EditingAsset.Get(), true); }
void FCFModelEditorToolkit::HandleModelError(const FString& Message)        { UE_LOG(LogTemp, Warning, TEXT("%s"), *Message); }
void FCFModelEditorToolkit::HandleModelErrorEx(const FCFModelError& Error)  { UE_LOG(LogTemp, Warning, TEXT("Code=%d Msg=%s Ctx=%s"), (int32)Error.Code, *Error.Message, *Error.Context); }

#undef LOCTEXT_NAMESPACE