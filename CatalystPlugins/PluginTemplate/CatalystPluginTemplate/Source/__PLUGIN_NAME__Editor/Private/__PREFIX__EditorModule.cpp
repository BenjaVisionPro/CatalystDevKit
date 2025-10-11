// ============================================================================
// Catalyst __PLUGIN_DISPLAY_NAME__ — Editor Module (AssetDefinition-driven)
// ----------------------------------------------------------------------------
// - Registers "Catalyst:__PLUGIN_DISPLAY_NAME__" Nomad tab + ToolMenus entry
// - Boots CE editor style/commands
// - NOTE: Add(+)/Content Browser placement is handled by UAssetDefinition
//         (e.g., U__PREFIX__AssetDefinition_Model::GetAssetCategories()).
// ============================================================================

#include "__PREFIX__EditorModule.h"

#include "__PREFIX__EditorStyle.h"
#include "__PREFIX__EditorCommands.h"
#include "UI/__PREFIX__ModelWidget.h"

#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/UnrealType.h"

#include "Model/__PREFIX__ModelAsset.h"
#include "Log/CFLog.h" // CF_* macros (no UE_LOG)

// ---- Optional diagnostics (compiled only in debug editor builds) ----
#if WITH_EDITOR && UE_BUILD_DEBUG
	#include "AssetDefinitionDefault.h"
	#include "Factories/Factory.h"
	#include "AssetDefinitions/CFAssetDefinition_Model.h"
	#include "AssetDefinitions/__PREFIX__AssetDefinition_Model.h"
	#include "Factories/__PREFIX__ModelAssetFactory.h"
#endif

DEFINE_LOG_CATEGORY(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor);

static const FName CatalystMenuName("Catalyst.Plugins");
static const FName CatalystEditorTabName("Catalyst:__PLUGIN_DISPLAY_NAME__");

static FDelegateHandle GToolMenusStartupHandle;

#define LOCTEXT_NAMESPACE "F__PREFIX__EditorModule"

#if WITH_EDITOR && UE_BUILD_DEBUG
static void CE_DumpCreationPath()
{
	// Foundation definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(UCFAssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display, TEXT("[Diag/Def:__PREFIX__] __PREFIX__AssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// __PLUGIN_DISPLAY_NAME__ definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(U__PREFIX__AssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display, TEXT("[Diag/Def:__PREFIX__] __PREFIX__AssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// __PLUGIN_DISPLAY_NAME__ factory
	if (const UFactory* FacCDO = Cast<UFactory>(U__PREFIX__ModelAssetFactory::StaticClass()->GetDefaultObject(false)))
	{
		CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display,
			TEXT("[Diag/Factory] __PREFIX__ModelAssetFactory  SupportedClass=%s  ShouldShowInNewMenu=%s  MenuCat=%u"),
			*GetNameSafe(FacCDO->SupportedClass),
			FacCDO->ShouldShowInNewMenu() ? TEXT("true") : TEXT("false"),
			FacCDO->GetMenuCategories());
	}
}
#endif // WITH_EDITOR && UE_BUILD_DEBUG

void F__PREFIX__EditorModule::StartupModule()
{
	GToolMenusStartupHandle = UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &F__PREFIX__EditorModule::RegisterMenus));

	F__PREFIX__EditorStyle::Initialize();
	F__PREFIX__EditorStyle::ReloadTextures();
	F__PREFIX__EditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		CatalystEditorTabName,
		FOnSpawnTab::CreateRaw(this, &F__PREFIX__EditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("__PREFIX___TabTitle_Default", "Catalyst:__PLUGIN_DISPLAY_NAME__"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display, TEXT("__PLUGIN_NAME__Editor Startup"));

#if WITH_EDITOR && UE_BUILD_DEBUG
	CE_DumpCreationPath();
#endif
}

void F__PREFIX__EditorModule::ShutdownModule()
{
	if (GToolMenusStartupHandle.IsValid())
	{
		UToolMenus::UnRegisterStartupCallback(GToolMenusStartupHandle);
		GToolMenusStartupHandle.Reset();
	}

	UToolMenus::UnregisterOwner(this);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystEditorTabName);

	CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display, TEXT("__PLUGIN_NAME__Editor Shutdown"));
}

void F__PREFIX__EditorModule::RegisterMenus()
{
	if (UToolMenus* TM = UToolMenus::Get())
	{
		if (UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName))
		{
			FToolMenuSection& Sec = Menu->AddSection("__PLUGIN_NAME__", LOCTEXT("__PLUGIN_NAME__", "Catalyst:__PLUGIN_DISPLAY_NAME__"));

			Sec.AddDynamicEntry(
				"__PLUGIN_DISPLAY_NAME__Entries",
				FNewToolMenuSectionDelegate::CreateRaw(this, &F__PREFIX__EditorModule::Build__PLUGIN_DISPLAY_NAME__Menu));
		}
	}
}

void F__PREFIX__EditorModule::Build__PLUGIN_DISPLAY_NAME__Menu(FToolMenuSection& Section)
{
	const bool bVisualizerRunning = false;
	const FText Label = bVisualizerRunning
		? LOCTEXT("Open__PLUGIN_DISPLAY_NAME___Running", "__PLUGIN_DISPLAY_NAME__ (Running)")
		: LOCTEXT("OpenE__PLUGIN_DISPLAY_NAME__", "__PLUGIN_DISPLAY_NAME__");

	Section.AddMenuEntry(
		"Open__PLUGIN_DISPLAY_NAME__Window",
		Label,
		LOCTEXT("Open__PLUGIN_DISPLAY_NAME__Desc", "Open the Catalyst:__PLUGIN_DISPLAY_NAME__ editor/visualiser."),
		FSlateIcon(F__PREFIX__EditorStyle::GetStyleSetName(), "__PREFIX__.ToolbarIcon40"),
		FUIAction(FExecuteAction::CreateRaw(this, &F__PREFIX__EditorModule::PluginButtonClicked)));
}

TSharedRef<SDockTab> F__PREFIX__EditorModule::OnSpawnPluginTab(const FSpawnTabArgs& Args)
{
	const FText TabLabel = Get__PLUGIN_DISPLAY_NAME__TabLabel();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(TabLabel)
		[
			SNew(S__PREFIX__ModelWidget)
			.Seed(1337)
		];
}

void F__PREFIX__EditorModule::PluginButtonClicked()
{
	CF_CAT_LOG(Log__PREFIX____PLUGIN_DISPLAY_NAME__Editor, Display, TEXT("F__PREFIX__EditorModule::PluginButtonClicked()"));
	FGlobalTabmanager::Get()->TryInvokeTab(CatalystEditorTabName);
}

FText F__PREFIX__EditorModule::Get__PLUGIN_DISPLAY_NAME__TabLabel() const
{
	static const FText DefaultTitle = LOCTEXT("_PREFIX___TabTitle_Default", "Catalyst:__PLUGIN_DISPLAY_NAME__");

	const FSoftObjectPath SeedPath(TEXT("/__PLUGIN_NAME__/Model/__PREFIX__ModelAsset_Seed.__PREFIX__ModelAsset_Seed"));
	if (U__PREFIX__ModelAsset* Asset = Cast<U__PREFIX__ModelAsset>(SeedPath.TryLoad()))
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

IMPLEMENT_MODULE(F__PREFIX__EditorModule, __PLUGIN_NAME__Editor)