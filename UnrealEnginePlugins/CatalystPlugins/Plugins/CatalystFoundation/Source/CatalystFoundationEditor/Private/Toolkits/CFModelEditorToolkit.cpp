#include "Toolkits/CFModelEditorToolkit.h"
#include "CFEditorModule.h" // LogCFEditor + FCFEditorAssetCategory::Get()

#include "Model/CFModelAsset.h"

#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBorder.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "FCFModelEditorToolkit"

const FName FCFModelEditorToolkit::DetailsTabId    = TEXT("CFModelEditorToolkit_Details");
const FName FCFModelEditorToolkit::ValidationTabId = TEXT("CFModelEditorToolkit_Validation");

FCFModelEditorToolkit::FCFModelEditorToolkit() = default;
FCFModelEditorToolkit::~FCFModelEditorToolkit() = default;

void FCFModelEditorToolkit::InitModelEditor(
	UCFModelAsset* InAsset,
	EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	check(InAsset);
	EditingAsset = InAsset;

	BuildDetailsPanel();

	// Layout: Details (open), Validation (closed by default)
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("CFModelEditorToolkit_Layout_v1")
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
			->AddTab(ValidationTabId, ETabState::ClosedTab)
		)
	);

	// Initialize base asset editor
	InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		/*bCreateDefaultStandaloneMenu*/ true,
		/*bCreateDefaultToolbar*/        true,
		EditingAsset
	);

	// Single-mode editor; no SetCurrentMode required on UE 5.6
}

void FCFModelEditorToolkit::BuildDetailsPanel()
{
	FPropertyEditorModule& PEM = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bUpdatesFromSelection = false;
	Args.bLockable = false;
	Args.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	// Args.NotifyHook = this; // Only if class derives from FNotifyHook

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
		// (Icon is set by spawner; avoid deprecated SDockTab::Icon)
		.Label(LOCTEXT("DetailsTabLabel", "Details"))
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FCFModelEditorToolkit::SpawnValidationTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("ValidationTabLabel", "Validation"))
		[
			SNew(SBorder)
			.Padding(8)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ValidationPlaceholder", "Validation output will appear here."))
			]
		];
}

#undef LOCTEXT_NAMESPACE