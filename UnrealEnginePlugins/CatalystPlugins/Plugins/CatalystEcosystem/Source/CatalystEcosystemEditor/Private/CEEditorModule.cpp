// ============================================================================
// Catalyst Ecosystem — Editor Module (AssetDefinition-driven)
// ----------------------------------------------------------------------------
// - Registers "Catalyst:Ecosystem" Nomad tab + ToolMenus entry
// - Boots CE editor style/commands
// - NOTE: Add(+)/Content Browser placement is handled by UAssetDefinition
//         (e.g., UCEAssetDefinition_Model::GetAssetCategories()).
// ============================================================================

#include "CEEditorModule.h"

#include "CEEditorStyle.h"
#include "CEEditorCommands.h"
#include "UI/SCEVisualizer.h"

#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/UnrealType.h"

#include "Model/CEModelAsset.h"
#include "Log/CFLog.h" // CF_* macros (no UE_LOG)

// ---- Optional diagnostics (compiled only in debug editor builds) ----
#if WITH_EDITOR && UE_BUILD_DEBUG
	#include "AssetDefinitionDefault.h"
	#include "Factories/Factory.h"
	#include "AssetDefinitions/CFAssetDefinition_Model.h"
	#include "AssetDefinitions/CEAssetDefinition_Model.h"
	#include "Factories/CEModelAssetFactory.h"
#endif

DEFINE_LOG_CATEGORY(LogCEEditor);

static const FName CatalystMenuName("Catalyst.Plugins");
static const FName CatalystEcosystemEditorTabName("Catalyst:Ecosystem");

static FDelegateHandle GToolMenusStartupHandle;

#define LOCTEXT_NAMESPACE "FCEEditorModule"

#if WITH_EDITOR && UE_BUILD_DEBUG
static void CE_DumpCreationPath()
{
	// Foundation definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(UCFAssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(LogCEEditor, Display, TEXT("[Diag/Def:CF] CFAssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// Ecosystem definition
	if (UAssetDefinition* DefCDO = Cast<UAssetDefinition>(UCEAssetDefinition_Model::StaticClass()->GetDefaultObject(false)))
	{
		const UClass* Target = DefCDO->GetAssetClass().LoadSynchronous();
		CF_CAT_LOG(LogCEEditor, Display, TEXT("[Diag/Def:CE] CEAssetDefinition_Model -> Target=%s  CategoryPaths=%d"),
			*GetNameSafe(Target), DefCDO->GetAssetCategories().Num());
	}

	// Ecosystem factory
	if (const UFactory* FacCDO = Cast<UFactory>(UCEModelAssetFactory::StaticClass()->GetDefaultObject(false)))
	{
		CF_CAT_LOG(LogCEEditor, Display,
			TEXT("[Diag/Factory] CEModelAssetFactory  SupportedClass=%s  ShouldShowInNewMenu=%s  MenuCat=%u"),
			*GetNameSafe(FacCDO->SupportedClass),
			FacCDO->ShouldShowInNewMenu() ? TEXT("true") : TEXT("false"),
			FacCDO->GetMenuCategories());
	}
}
#endif // WITH_EDITOR && UE_BUILD_DEBUG

void FCEEditorModule::StartupModule()
{
	GToolMenusStartupHandle = UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCEEditorModule::RegisterMenus));

	FCEEditorStyle::Initialize();
	FCEEditorStyle::ReloadTextures();
	FCEEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		CatalystEcosystemEditorTabName,
		FOnSpawnTab::CreateRaw(this, &FCEEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("CE_TabTitle_Default", "Catalyst:Ecosystem"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	CF_CAT_LOG(LogCEEditor, Display, TEXT("CatalystEcosystemEditor Startup"));

#if WITH_EDITOR && UE_BUILD_DEBUG
	CE_DumpCreationPath();
#endif
}

void FCEEditorModule::ShutdownModule()
{
	if (GToolMenusStartupHandle.IsValid())
	{
		UToolMenus::UnRegisterStartupCallback(GToolMenusStartupHandle);
		GToolMenusStartupHandle.Reset();
	}

	UToolMenus::UnregisterOwner(this);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CatalystEcosystemEditorTabName);

	CF_CAT_LOG(LogCEEditor, Display, TEXT("CatalystEcosystemEditor Shutdown"));
}

void FCEEditorModule::RegisterMenus()
{
	if (UToolMenus* TM = UToolMenus::Get())
	{
		if (UToolMenu* Menu = TM->ExtendMenu(CatalystMenuName))
		{
			FToolMenuSection& Sec = Menu->AddSection("CatalystEcosystem", LOCTEXT("CatalystEcosystem", "Catalyst:Ecosystem"));

			Sec.AddDynamicEntry(
				"EcosystemEntries",
				FNewToolMenuSectionDelegate::CreateRaw(this, &FCEEditorModule::BuildEcosystemMenu));
		}
	}
}

void FCEEditorModule::BuildEcosystemMenu(FToolMenuSection& Section)
{
	const bool bVisualizerRunning = false;
	const FText Label = bVisualizerRunning
		? LOCTEXT("OpenEcosystem_Running", "Ecosystem (Running)")
		: LOCTEXT("OpenEcosystem", "Ecosystem");

	Section.AddMenuEntry(
		"OpenEcosystemWindow",
		Label,
		LOCTEXT("OpenEcosystemDesc", "Open the Catalyst:Ecosystem editor/visualiser."),
		FSlateIcon(FCEEditorStyle::GetStyleSetName(), "CE.ToolbarIcon40"),
		FUIAction(FExecuteAction::CreateRaw(this, &FCEEditorModule::PluginButtonClicked)));
}

TSharedRef<SDockTab> FCEEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& Args)
{
	const FText TabLabel = GetEcosystemTabLabel();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(TabLabel)
		[
			SNew(SCEVisualizer)
			.Seed(1337)
		];
}

void FCEEditorModule::PluginButtonClicked()
{
	CF_CAT_LOG(LogCEEditor, Display, TEXT("FCEEditorModule::PluginButtonClicked()"));
	FGlobalTabmanager::Get()->TryInvokeTab(CatalystEcosystemEditorTabName);
}

FText FCEEditorModule::GetEcosystemTabLabel() const
{
	static const FText DefaultTitle = LOCTEXT("CE_TabTitle_Default", "Catalyst:Ecosystem");

	const FSoftObjectPath SeedPath(TEXT("/CatalystEcosystem/Model/CEModelAsset_Seed.CEModelAsset_Seed"));
	if (UCEModelAsset* Asset = Cast<UCEModelAsset>(SeedPath.TryLoad()))
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

IMPLEMENT_MODULE(FCEEditorModule, CatalystEcosystemEditor)