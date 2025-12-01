// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CLEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCLEditorStyle::StyleInstance = nullptr;

void FCLEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCLEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCLEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CLEditorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> FCLEditorStyle::Create()
{
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("CLEditorStyle"));

    // Content root = <CatalystLandform>/Resources/Icons
    Style->SetContentRoot(IPluginManager::Get().FindPlugin("CatalystLandform")->GetBaseDir() / TEXT("Resources/Icons"));

    // Logo / main button icon
    Style->Set("CL.Logo64", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(64, 64)));

    // Example additional sized variant (if you really want 40px specifically)
    Style->Set("CL.ToolbarIcon40", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(40, 40)));

    return Style;
}

void FCLEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCLEditorStyle::Get()
{
	return *StyleInstance;
}
