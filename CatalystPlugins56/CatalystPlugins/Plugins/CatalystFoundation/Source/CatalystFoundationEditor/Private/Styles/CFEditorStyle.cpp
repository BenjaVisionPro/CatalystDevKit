#include "Styles/CFEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/AppStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h" // FPaths::ProjectContentDir

TSharedPtr<FSlateStyleSet> FCFEditorStyle::Style;

FName FCFEditorStyle::GetStyleSetName()
{
	static FName StyleName(TEXT("CatalystFoundationEditor"));
	return StyleName;
}

void FCFEditorStyle::Register()
{
	if (Style.IsValid())
	{
		return; // already registered (hot-reload safe)
	}

	Style = MakeShared<FSlateStyleSet>(GetStyleSetName());

	// Set content root to the plugin's Resources folder (SVGs etc.)
	if (TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("CatalystFoundation")))
	{
		Style->SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));
	}
	else
	{
		// Fallback: project content root
		Style->SetContentRoot(FPaths::ProjectContentDir());
	}

	// Local helper bound to this style's content root (no macro, no collisions).
	auto* StylePtr = Style.Get();
	auto MakeSvgBrush = [StylePtr](const TCHAR* RelativePath, const FVector2D& Size) -> FSlateVectorImageBrush*
	{
		return new FSlateVectorImageBrush(
			StylePtr->RootToContentDir(RelativePath, TEXT(".svg")),
			Size);
	};

	const FVector2D Icon16(16.f, 16.f);
	const FVector2D Icon64(64.f, 64.f);

	// Example icons for UCFModelAsset
	Style->Set(TEXT("ClassIcon.UCFModelAsset"),      static_cast<FSlateBrush*>(MakeSvgBrush(TEXT("Icons/Model"), Icon16)));
	Style->Set(TEXT("ClassThumbnail.UCFModelAsset"), static_cast<FSlateBrush*>(MakeSvgBrush(TEXT("Icons/Model"), Icon64)));

	FSlateStyleRegistry::RegisterSlateStyle(*Style.Get());
}

void FCFEditorStyle::Unregister()
{
	if (!Style.IsValid())
	{
		return;
	}
	FSlateStyleRegistry::UnRegisterSlateStyle(*Style.Get());
	Style.Reset();
}

const ISlateStyle& FCFEditorStyle::Get()
{
	if (!Style.IsValid())
	{
		Register();
	}
	return *Style.Get();
}