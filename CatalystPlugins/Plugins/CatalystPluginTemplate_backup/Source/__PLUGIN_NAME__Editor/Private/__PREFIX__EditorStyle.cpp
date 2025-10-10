// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "__PREFIX__EditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> F__PREFIX__EditorStyle::StyleInstance = nullptr;

void F__PREFIX__EditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void F__PREFIX__EditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName F__PREFIX__EditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("__PREFIX__EditorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> F__PREFIX__EditorStyle::Create()
{
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("__PREFIX__EditorStyle"));

    // Content root = <__PLUGIN_NAME__>/Resources/Icons
    Style->SetContentRoot(IPluginManager::Get().FindPlugin("__PLUGIN_NAME__")->GetBaseDir() / TEXT("Resources/Icons"));

    // Logo / main button icon
    Style->Set("__PREFIX__.Logo64", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(64, 64)));

    // Example additional sized variant (if you really want 40px specifically)
    Style->Set("__PREFIX__.ToolbarIcon40", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(40, 40)));

    return Style;
}

void F__PREFIX__EditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& F__PREFIX__EditorStyle::Get()
{
	return *StyleInstance;
}
