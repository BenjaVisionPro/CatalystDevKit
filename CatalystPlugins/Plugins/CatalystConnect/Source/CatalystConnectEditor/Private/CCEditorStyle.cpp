// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CCEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Fonts/SlateFontInfo.h"
#include "Fonts/CompositeFont.h" // FCompositeFont, FTypeface, FTypefaceEntry

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCCEditorStyle::StyleInstance = nullptr;

void FCCEditorStyle::Initialize()
{
    if (!StyleInstance.IsValid())
    {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
    }
}

void FCCEditorStyle::Shutdown()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
    ensure(StyleInstance.IsUnique());
    StyleInstance.Reset();
}

FName FCCEditorStyle::GetStyleSetName()
{
    static FName StyleSetName(TEXT("CCEditorStyle"));
    return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef<FSlateStyleSet> FCCEditorStyle::Create()
{
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("CCEditorStyle"));

    // Plugin paths
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("CatalystConnect"));
    const FString BaseDir  = Plugin.IsValid() ? Plugin->GetBaseDir() : FString();
    const FString IconsDir = BaseDir / TEXT("Resources/Icons");
    const FString FontsDir = BaseDir / TEXT("Resources/Fonts");

    // Set icon root
    Style->SetContentRoot(IconsDir);

    // ===========================
    // Image brushes (existing)
    // ===========================
    Style->Set("CCEditor.EditorTools", new IMAGE_BRUSH(TEXT("ccButtonIcon40"), Icon40x40));

    // ===========================
    // Font registrations (5.6+)
    // ===========================
    auto MakeFont = [&](const FString& FileName, int32 Size) -> FSlateFontInfo
    {
        // Build a shared composite font with a single typeface entry from file
        TSharedRef<FCompositeFont> Composite = MakeShared<FCompositeFont>();
        FTypeface& Typeface = Composite->DefaultTypeface;
        Typeface.Fonts.Add(
            FTypefaceEntry(
                FName(TEXT("Default")),
                FString(FontsDir / FileName),
                EFontHinting::Auto,
                EFontLoadingPolicy::LazyLoad
            )
        );

        // FSlateFontInfo wants a shared pointer to the composite font
        return FSlateFontInfo(Composite, static_cast<float>(Size));
    };

    // ---- Bebas Neue Pro (text) ----
    Style->Set("CC.Font.HeadingXL", MakeFont(TEXT("BebasNeuePro-Bold.otf"),    32));
    Style->Set("CC.Font.HeadingL",  MakeFont(TEXT("BebasNeuePro-Bold.otf"),    24));
    Style->Set("CC.Font.HeadingM",  MakeFont(TEXT("BebasNeuePro-Regular.otf"), 20));
    Style->Set("CC.Font.Body",      MakeFont(TEXT("BebasNeuePro-Book.otf"),    14));
    Style->Set("CC.Font.Light",     MakeFont(TEXT("BebasNeuePro-Light.otf"),   14));

    // ---- Font Awesome 5 Pro (icons) ----
    Style->Set("CC.Icon.Light.16",  MakeFont(TEXT("Font Awesome 5 Pro-Light-300.otf"),    16));
    Style->Set("CC.Icon.Light.20",  MakeFont(TEXT("Font Awesome 5 Pro-Light-300.otf"),    20));
    Style->Set("CC.Icon.Reg.20",    MakeFont(TEXT("Font Awesome 5 Pro-Regular-400.otf"),  20));
    Style->Set("CC.Icon.Reg.24",    MakeFont(TEXT("Font Awesome 5 Pro-Regular-400.otf"),  24));
    Style->Set("CC.Icon.Solid.24",  MakeFont(TEXT("Font Awesome 5 Pro-Solid-900.otf"),    24));
    Style->Set("CC.Icon.Solid.32",  MakeFont(TEXT("Font Awesome 5 Pro-Solid-900.otf"),    32));
    Style->Set("CC.Icon.Solid.40",  MakeFont(TEXT("Font Awesome 5 Pro-Solid-900.otf"),    40));

    // Handy default alias
    Style->Set("CC.Icon", Style->GetFontStyle("CC.Icon.Solid.24"));

    return Style;
}

void FCCEditorStyle::ReloadTextures()
{
    if (FSlateApplication::IsInitialized())
    {
        FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
    }
}

const ISlateStyle& FCCEditorStyle::Get()
{
    return *StyleInstance;
}
