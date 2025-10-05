#include "Styles/CFEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/AppStyle.h"
#include "Interfaces/IPluginManager.h"

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
		// Fallback: project content root (still allows dev to place Resources here)
		Style->SetContentRoot(FPaths::ProjectContentDir());
	}

	// Local macro that sees the Style pointer (scoped to this function)
	auto* StylePtr = Style.Get();
	#define IMAGE_BRUSH_SVG(RelativePath, Size) FSlateVectorImageBrush(StylePtr->RootToContentDir(RelativePath, TEXT(".svg")), Size)

	const FVector2D Icon16(16.f, 16.f);
	const FVector2D Icon64(64.f, 64.f);

	// Example: provide default icon/thumbnail for the base model asset class
	// Feature plugins can add their own keys/classes in their editor modules.
	Style->Set(TEXT("ClassIcon.UCFModelAsset"),      new IMAGE_BRUSH_SVG(TEXT("Icons/Model"), Icon16));
	Style->Set(TEXT("ClassThumbnail.UCFModelAsset"), new IMAGE_BRUSH_SVG(TEXT("Icons/Model"), Icon64));

	#undef IMAGE_BRUSH_SVG

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