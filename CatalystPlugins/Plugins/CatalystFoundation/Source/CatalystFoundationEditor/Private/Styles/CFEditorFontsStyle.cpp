// ============================================
// Catalyst:Foundation - Shared Editor Fonts Style
// ============================================

#include "Styles/CFEditorFontsStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Fonts/CompositeFont.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateStyleMacros.h"
#include "Misc/Paths.h"

TSharedPtr<FSlateStyleSet> FCFEditorFontsStyle::StyleInstance = nullptr;

// Font Awesome (icons)
const FName FCFEditorFontsStyle::IconSolid16   = "CF.Fonts.Icon.Solid.16";
const FName FCFEditorFontsStyle::IconSolid24   = "CF.Fonts.Icon.Solid.24";
const FName FCFEditorFontsStyle::IconSolid32   = "CF.Fonts.Icon.Solid.32";
const FName FCFEditorFontsStyle::IconSolid48   = "CF.Fonts.Icon.Solid.48";
const FName FCFEditorFontsStyle::IconRegular24 = "CF.Fonts.Icon.Regular.24";
const FName FCFEditorFontsStyle::IconLight24   = "CF.Fonts.Icon.Light.24";

// Generic display/body
const FName FCFEditorFontsStyle::FontDisplay32 = "CF.Fonts.Display.32";
const FName FCFEditorFontsStyle::FontBody12    = "CF.Fonts.Body.12";

// BebasNeuePro family (20pt examples)
const FName FCFEditorFontsStyle::BebasBold20    = "CF.Fonts.Bebas.Bold.20";
const FName FCFEditorFontsStyle::BebasBook20    = "CF.Fonts.Bebas.Book.20";
const FName FCFEditorFontsStyle::BebasLight20   = "CF.Fonts.Bebas.Light.20";
const FName FCFEditorFontsStyle::BebasMiddle20  = "CF.Fonts.Bebas.Middle.20";
const FName FCFEditorFontsStyle::BebasRegular20 = "CF.Fonts.Bebas.Regular.20";
const FName FCFEditorFontsStyle::BebasThin20    = "CF.Fonts.Bebas.Thin.20";

void FCFEditorFontsStyle::Initialize()
{
    if (!StyleInstance.IsValid())
    {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
    }
}

void FCFEditorFontsStyle::Shutdown()
{
    if (StyleInstance.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
        ensure(StyleInstance.IsUnique());
        StyleInstance.Reset();
    }
}

FName FCFEditorFontsStyle::GetStyleSetName()
{
    static FName Name(TEXT("CFEditorFontsStyle"));
    return Name;
}

const ISlateStyle& FCFEditorFontsStyle::Get()
{
    check(StyleInstance.IsValid());
    return *StyleInstance.Get();
}

static TSharedPtr<const FCompositeFont> MakeComposite(const FString& FontPath)
{
    TSharedRef<FCompositeFont> Composite = MakeShared<FCompositeFont>();
    FTypeface& Typeface = Composite->DefaultTypeface;

    Typeface.Fonts.Add(FTypefaceEntry(
        FName(TEXT("Default")),
        FontPath,
        EFontHinting::Auto,
        EFontLoadingPolicy::LazyLoad));

    return Composite;
}

TSharedRef<FSlateStyleSet> FCFEditorFontsStyle::Create()
{
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));

    // Fonts now live in the Foundation plugin
    const TSharedPtr<IPlugin> Plug = IPluginManager::Get().FindPlugin(TEXT("CatalystFoundation"));
    const FString BaseDir  = Plug.IsValid() ? Plug->GetBaseDir() : (FPaths::ProjectPluginsDir() / TEXT("CatalystFoundation"));
    const FString FontsDir = BaseDir / TEXT("Resources/Fonts");

    // Font Awesome
    const FString FA_Solid   = FontsDir / TEXT("Font Awesome 5 Pro-Solid-900.otf");
    const FString FA_Regular = FontsDir / TEXT("Font Awesome 5 Pro-Regular-400.otf");
    const FString FA_Light   = FontsDir / TEXT("Font Awesome 5 Pro-Light-300.otf");

    // BebasNeuePro
    const FString Bebas_Bold   = FontsDir / TEXT("BebasNeuePro-Bold.otf");
    const FString Bebas_Book   = FontsDir / TEXT("BebasNeuePro-Book.otf");
    const FString Bebas_Light  = FontsDir / TEXT("BebasNeuePro-Light.otf");
    const FString Bebas_Middle = FontsDir / TEXT("BebasNeuePro-Middle.otf");
    const FString Bebas_Reg    = FontsDir / TEXT("BebasNeuePro-Regular.otf");
    const FString Bebas_Thin   = FontsDir / TEXT("BebasNeuePro-Thin.otf");

    // Build composite fonts
    const TSharedPtr<const FCompositeFont> CompFA_Solid   = MakeComposite(FA_Solid);
    const TSharedPtr<const FCompositeFont> CompFA_Regular = MakeComposite(FA_Regular);
    const TSharedPtr<const FCompositeFont> CompFA_Light   = MakeComposite(FA_Light);

    const TSharedPtr<const FCompositeFont> CompBebasBold   = MakeComposite(Bebas_Bold);
    const TSharedPtr<const FCompositeFont> CompBebasBook   = MakeComposite(Bebas_Book);
    const TSharedPtr<const FCompositeFont> CompBebasLight  = MakeComposite(Bebas_Light);
    const TSharedPtr<const FCompositeFont> CompBebasMiddle = MakeComposite(Bebas_Middle);
    const TSharedPtr<const FCompositeFont> CompBebasReg    = MakeComposite(Bebas_Reg);
    const TSharedPtr<const FCompositeFont> CompBebasThin   = MakeComposite(Bebas_Thin);

    // Register Font Awesome icon sizes
    Style->Set(IconSolid16,   FSlateFontInfo(CompFA_Solid,   16.f));
    Style->Set(IconSolid24,   FSlateFontInfo(CompFA_Solid,   24.f));
    Style->Set(IconSolid32,   FSlateFontInfo(CompFA_Solid,   32.f));
    Style->Set(IconSolid48,   FSlateFontInfo(CompFA_Solid,   48.f));
    Style->Set(IconRegular24, FSlateFontInfo(CompFA_Regular, 24.f));
    Style->Set(IconLight24,   FSlateFontInfo(CompFA_Light,   24.f));

    // Register Bebas weights (20pt)
    Style->Set(BebasBold20,    FSlateFontInfo(CompBebasBold,   20.f));
    Style->Set(BebasBook20,    FSlateFontInfo(CompBebasBook,   20.f));
    Style->Set(BebasLight20,   FSlateFontInfo(CompBebasLight,  20.f));
    Style->Set(BebasMiddle20,  FSlateFontInfo(CompBebasMiddle, 20.f));
    Style->Set(BebasRegular20, FSlateFontInfo(CompBebasReg,    20.f));
    Style->Set(BebasThin20,    FSlateFontInfo(CompBebasThin,   20.f));

    // Generic convenience
    Style->Set(FontDisplay32, FSlateFontInfo(CompBebasReg, 32.f));
    Style->Set(FontBody12,    FSlateFontInfo(CompBebasReg, 12.f));

    return Style;
}
