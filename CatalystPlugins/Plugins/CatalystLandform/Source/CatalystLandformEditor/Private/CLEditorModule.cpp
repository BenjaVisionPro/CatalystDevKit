// ============================================================================
// Catalyst Landform — Editor Module (AssetDefinition-driven)
// ----------------------------------------------------------------------------
// - Registers "Catalyst:Landform" Nomad tab + ToolMenus entry
// - Boots CE editor style/commands
// - NOTE: Add(+)/Content Browser placement is handled by UAssetDefinition
//         (e.g., UCLAssetDefinition_Model::GetAssetCategories()).
// ============================================================================

#include "CLEditorModule.h"

#include "CLEditorStyle.h"
#include "CLEditorCommands.h"
#include "UI/CLModelWidget.h"

#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/UnrealType.h"

#include "Model/CLModelAsset.h"
#include "Log/CFLog.h" // CF_* macros (no UE_LOG)

// ---- Optional diagnostics (compiled only in debug editor builds) ----
#if WITH_EDITOR && UE_BUILD_DEBUG
	#include "AssetDefinitionDefault.h"
	#include "Factories/Factory.h"
	#include "AssetDefinitions/CFAssetDefinition_Model.h"
	#include "AssetDefinitions/CLAssetDefinition_Model.h"
	#include "Factories/CLModelAssetFactory.h"
#endif

DEFINE_LOG_CATEGORY(LogCLLandformEditor);

static const FName CatalystMenuName("Catalyst.Plugins");
static const FName CatalystEditorTabName("Catalyst:Landform");

static FDelegateHandle GToolMenusStartupHandle;

#define LOCTEXT_NAMESPACE "FCLEditorModule"

#if WITH_EDITOR && UE_BUILD_DEBUG
static void CE_DumpCreationPath()
{
	// Foundation definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(UCFAssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(LogCLLandformEditor, Display, TEXT("[Diag/Def:CL] CLAssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// Landform definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(UCLAssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(LogCLLandformEditor, Display, TEXT("[Diag/Def:CL] CLAssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// Landform factory
	if (const UFactory* FacCDO = Cast<UFactory>(UCLModelAssetFactory::StaticClass()->GetDefaultObject(false)))
	{
		CF_CAT_LOG(LogCLLandformEditor, Display,
			TEXT("[Diag/Factory] CLModelAssetFactory  SupportedClass=%s  ShouldShowInNewMenu=%s  MenuCat=%u"),
			*GetNameSafe(FacCDO->SupportedClass),
			FacCDO->ShouldShowInNewMenu() ? TEXT("true") : TEXT("false"),
			FacCDO->GetMenuCategories());
	}
}
#endif // WITH_EDITOR && UE_BUILD_DEBUG

void FCLEditorModule::StartupModule()
{
	GToolMenusStartupHandle = UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCLEditorModule::RegisterMenus));

	FCLEditorStyle::Initialize();
	FCLEditorStyle::ReloadTextures();
	FCLEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		CatalystEditorTabName,
		FOnSpawnTab::CreateRaw(this, &FCLEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("CL_TabTitle_Default", "Catalyst:Landform"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	CF_CAT_LOG(LogCLLandformEditor, Display, TEXT("CatalystLandformEditor Startup"));

#if WITH_EDITOR && UE_BUILD_DEBUG
	CE_DumpCreationPath();
#endif
}

void FCLEditorModule::ShutdownModule()
{
	if (GToolMenusStartupHandle.IsValid())
	{
		UToolMenus::UnRegisterStartupCallback(GToolMenusStartupHandle);
		GToolMenusStartupHandle.Reset();
	}

	UToolMenus::UnregisterOwner(this);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystEditorTabName);

	CF_CAT_LOG(LogCLLandformEditor, Display, TEXT("CatalystLandformEditor Shutdown"));
}

void FCLEditorModule::RegisterMenus()
{
	if (UToolMenus* TM = UToolMenus::Get())
	{
		if (UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName))
		{
			FToolMenuSection& Sec = Menu->AddSection("CatalystLandform", LOCTEXT("CatalystLandform", "Catalyst:Landform"));

			Sec.AddDynamicEntry(
				"LandformEntries",
				FNewToolMenuSectionDelegate::CreateRaw(this, &FCLEditorModule::BuildLandformMenu));
		}
	}
}

void FCLEditorModule::BuildLandformMenu(FToolMenuSection& Section)
{
	const bool bVisualizerRunning = false;
	const FText Label = bVisualizerRunning
		? LOCTEXT("OpenLandform_Running", "Landform (Running)")
		: LOCTEXT("OpenELandform", "Landform");

	Section.AddMenuEntry(
		"OpenLandformWindow",
		Label,
		LOCTEXT("OpenLandformDesc", "Open the Catalyst:Landform editor/visualiser."),
		FSlateIcon(FCLEditorStyle::GetStyleSetName(), "CL.ToolbarIcon40"),
		FUIAction(FExecuteAction::CreateRaw(this, &FCLEditorModule::PluginButtonClicked)));
}

TSharedRef<SDockTab> FCLEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& Args)
{
	const FText TabLabel = GetLandformTabLabel();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(TabLabel)
		[
			SNew(SCLModelWidget)
			.Seed(1337)
		];
}

void FCLEditorModule::PluginButtonClicked()
{
	CF_CAT_LOG(LogCLLandformEditor, Display, TEXT("FCLEditorModule::PluginButtonClicked()"));
	FGlobalTabmanager::Get()->TryInvokeTab(CatalystEditorTabName);
}

FText FCLEditorModule::GetLandformTabLabel() const
{
	static const FText DefaultTitle = LOCTEXT("_PREFIX___TabTitle_Default", "Catalyst:Landform");

	const FSoftObjectPath SeedPath(TEXT("/CatalystLandform/Model/CLModelAsset_Seed.CLModelAsset_Seed"));
	if (UCLModelAsset* Asset = Cast<UCLModelAsset>(SeedPath.TryLoad()))
	{
		if (FProperty* ModelProp = Asset->GetClass()->FindPropertyByName(TEXT("Model")))
		{
			if (FStructProperty* StructProp = CastField<FStructProperty>(ModelProp))
			{
				void* ModelPtr = StructProp->ContainerPtrToValuePtr<void>(Asset);
				if (UScriptStruct* ModelStruct = StructProp->Struct)
				{
					if (FProperty* TitleProp = ModelStruct->FindPropertyByName(TEXT("Title")))
					{
						if (FStrProperty* StrProp = CastField<FStrProperty>(TitleProp))
						{
							const FString Title = StrProp->GetPropertyValue_InContainer(ModelPtr);
							if (!Title.IsEmpty())
							{
								return FText::FromString(Title);
							}
						}
					}
				}
			}
		}

		if (Asset->GetFName() != NAME_None)
		{
			return FText::FromName(Asset->GetFName());
		}
	}

	return DefaultTitle;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCLEditorModule, CatalystLandformEditor)