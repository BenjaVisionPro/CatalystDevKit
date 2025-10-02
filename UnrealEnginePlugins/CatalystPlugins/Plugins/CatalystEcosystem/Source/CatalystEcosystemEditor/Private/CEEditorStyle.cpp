// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CEEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCEEditorStyle::StyleInstance = nullptr;

void FCEEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCEEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCEEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CEEditorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> FCEEditorStyle::Create()
{
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("CEEditorStyle"));

    // Content root = <CatalystEcosystem>/Resources/Icons
    Style->SetContentRoot(IPluginManager::Get().FindPlugin("CatalystEcosystem")->GetBaseDir() / TEXT("Resources/Icons"));

    // Logo / main button icon
    Style->Set("CE.Logo64", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(64, 64)));

    // Example additional sized variant (if you really want 40px specifically)
    Style->Set("CE.ToolbarIcon40", new IMAGE_BRUSH_SVG(TEXT("ceButtonIcon"), FVector2D(40, 40)));

    return Style;
}

void FCEEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCEEditorStyle::Get()
{
	return *StyleInstance;
}
