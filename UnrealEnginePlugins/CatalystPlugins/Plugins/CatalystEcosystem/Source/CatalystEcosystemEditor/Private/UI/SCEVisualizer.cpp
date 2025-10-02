// ============================================
// Catalyst:Ecosystem Visualizer (Dashboard)
// ============================================

#include "UI/SCEVisualizer.h"

#include "Styling/SlateTypes.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateBrush.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SOverlay.h"

#include "Styles/CFEditorFontsStyle.h"   // foundation shared Font Awesome + Bebas
#include "CEEditorStyle.h"        // provides CE brushes (e.g. CE.Logo64)
#include "UI/CEFontAwesome.h"     // FA glyph constants
#include "UI/Panels/SCESummaryPanel.h"


namespace
{
    // Tile metrics
    constexpr float kTileHeight = 60.f;     // card height
    constexpr float kAspect     = 2.2f;     // width = height * 2.4
    constexpr float kTileWidth  = kTileHeight * kAspect;

    const FMargin kCardPad(14.f);           // inner padding/inset

    // Font Awesome LIGHT icon, sized to a target pixel height
    TSharedRef<STextBlock> MakeFAIconLightSized(const TCHAR* Glyph, float PixelSize)
    {
        FSlateFontInfo IconFont = FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::IconLight24);
        IconFont.Size = PixelSize;
        return SNew(STextBlock)
            .Font(IconFont)
            .Text(FText::FromString(Glyph));
    }

    // 6px status dot (color provided)
    TSharedRef<SWidget> MakeStatusDotBR(const FLinearColor& Color)
    {
        return SNew(SBorder)
            .Padding(0.f)
            .BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
            .BorderBackgroundColor(Color)
            [
                SNew(SBox).WidthOverride(6.f).HeightOverride(6.f)
            ];
    }
}

void SCEVisualizer::Construct(const FArguments& InArgs)
{
    PreviewSeed = InArgs._Seed;

    // TODO: replace with live counts
    EcosystemCount = 6;
    BiomeCount     = 48;
    SpeciesCount   = 36;
    ResourceCount  = 185;

    const FLinearColor OK   = FLinearColor(0.12f, 0.80f, 0.32f);
    const FLinearColor WARN = FLinearColor(0.98f, 0.73f, 0.08f);
    const FLinearColor ERR  = FLinearColor(0.86f, 0.20f, 0.20f);
    const FLinearColor NEUT = FLinearColor(0.55f, 0.55f, 0.55f);

    ChildSlot
    [
        SNew(SBorder)
        .Padding(12.f)
        [
            SNew(SVerticalBox)

            // ===== Header with logo, tiles, and settings =====
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)

                // Logo (left) – clickable to open Summary
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                [
                    SNew(SButton)
                    .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
                    .ContentPadding(0.f)
                    .OnClicked(this, &SCEVisualizer::OnOpenSummary)
                    [
                        SNew(SImage)
                        .Image(FCEEditorStyle::Get().GetBrush("CE.Logo64"))
                        .ToolTipText(NSLOCTEXT("CE", "DashTitle", "Catalyst: Summary / News"))
                    ]
                ]

                // Spacer between logo and tiles
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(24.f, 0.f)
                [
                    SNullWidget::NullWidget
                ]

                // Tiles (center, evenly distributed)
                + SHorizontalBox::Slot()
                .FillWidth(1.f)
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
                    SNew(SHorizontalBox)

                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::Globe, EcosystemCount, OK,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenEcosystems))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::Leaf, BiomeCount, OK,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenBiomes))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::Paw, SpeciesCount, OK,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenSpecies))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::Cubes, ResourceCount, WARN,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenResources))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::CloudSun, TOptional<int32>(), NEUT,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenWeather))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(CEFA::SlidersH, TOptional<int32>(), OK,
                            FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenSimulations))
                    ]
                ]

                // Spacer between tiles and settings
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(24.f, 0.f)
                [
                    SNullWidget::NullWidget
                ]

                // Settings (right)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                .Padding(8.f, 0.f)
                [
                    SNew(SButton)
                    .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
                    .ContentPadding(FMargin(6,4))
                    .ToolTipText(NSLOCTEXT("CE","SettingsTT","Settings"))
                    .OnClicked(this, &SCEVisualizer::OnOpenSettings)
                    [
                        MakeFAIconLightSized(CEFA::Cog, 24.f)
                    ]
                ]
            ]

            // Divider
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.f, 8.f)
            [
                SNew(SSeparator)
            ]

            // ===== Panel host =====
            + SVerticalBox::Slot()
            .FillHeight(1.f)
            [
                SNew(SBorder)
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                [
                    SAssignNew(PanelHost, SBox)
                ]
            ]
        ]
    ];

    // Default view
    ShowPanel(ECEPanelKind::Summary);
}

/* ---------- Tile builder ---------- */

TSharedRef<SWidget> SCEVisualizer::MakeIconTile(
    const TCHAR* Glyph,
    TOptional<int32> Count,
    const FLinearColor StatusColor,
    FOnClicked OnClicked)
{
    // Scale icon to fit tile height (leave breathing room within padding)
    const float IconPx = FMath::Clamp(
        (kTileHeight - (kCardPad.Top + kCardPad.Bottom)) * 0.72f,
        18.f, 56.f);

    // Bebas Bold for the numeric count
    FSlateFontInfo CountFont = FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::BebasBold20);
    CountFont.Size = 18.f;

    return SNew(SButton)
        .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
        .ContentPadding(0.f)
        .OnClicked(OnClicked)
        [
            // Fixed aspect card (2.4 : 1)
            SNew(SBox)
            .WidthOverride(kTileWidth)
            .HeightOverride(kTileHeight)
            [
                SNew(SBorder)
                .Padding(kCardPad)
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                [
                    SNew(SOverlay)

                    // Left: outlined icon, vertically centered
                    + SOverlay::Slot()
                    .HAlign(HAlign_Left)
                    .VAlign(VAlign_Center)
                    [
                        MakeFAIconLightSized(Glyph, IconPx)
                    ]

                    // Right: vertical column that is vertically centered and
                    // internally centers both the number and the dot horizontally.
                    + SOverlay::Slot()
                    .HAlign(HAlign_Right)
                    .VAlign(VAlign_Center)
                    [
                        SNew(SVerticalBox)

                        // Number (if provided)
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Center)
                        .Padding(FMargin(0.f, 0.f, 0.f, 4.f)) // gap above the dot
                        [
                            SNew(SBox)
                            .Visibility(Count.IsSet() ? EVisibility::Visible : EVisibility::Collapsed)
                            [
                                SNew(STextBlock)
                                .Font(CountFont)
                                .Justification(ETextJustify::Center)
                                .Text(FText::AsNumber(Count.Get(0)))
                            ]
                        ]

                        // Status dot (always shown)
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Center)
                        [
                            MakeStatusDotBR(StatusColor)
                        ]
                    ]
                ]
            ]
        ];
}

/* ---------- Panels ---------- */

void SCEVisualizer::ShowPanel(ECEPanelKind Kind)
{
    if (!PanelHost.IsValid())
        return;

    if (ActivePanel == Kind)
        return;

    if (TWeakPtr<SWidget>* Found = PanelCache.Find(Kind))
    {
        if (TSharedPtr<SWidget> Existing = Found->Pin())
        {
            PanelHost->SetContent(Existing.ToSharedRef());
            ActivePanel = Kind;
            return;
        }
    }

    // Build on demand and cache
    TSharedRef<SWidget> NewPanel = BuildPanel(Kind);
    PanelCache.Add(Kind, NewPanel);
    PanelHost->SetContent(NewPanel);
    ActivePanel = Kind;
}

TSharedRef<SWidget> SCEVisualizer::BuildTitledPanel(const FText& Title)
{
    // Simple placeholder layout you can replace with real editors
    return SNew(SVerticalBox)
    + SVerticalBox::Slot()
    .AutoHeight()
    .Padding(8.f)
    [
        SNew(STextBlock)
        .Font(FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::FontDisplay32))
        .Text(Title)
    ]
    + SVerticalBox::Slot()
    .FillHeight(1.f)
    .Padding(8.f)
    [
        SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.DarkGroupBorder"))
    ];
}

TSharedRef<SWidget> SCEVisualizer::BuildPanel(ECEPanelKind Kind)
{
    switch (Kind)
    {
        case ECEPanelKind::Summary:
            return SNew(SCESummaryPanel).Title(NSLOCTEXT("CE", "SummaryPanel", "Summary / News"));

        // For now, placeholders for the rest until their concrete panels exist:
        case ECEPanelKind::Ecosystems:
        case ECEPanelKind::Biomes:
        case ECEPanelKind::Species:
        case ECEPanelKind::Resources:
        case ECEPanelKind::Weather:
        case ECEPanelKind::Simulations:
        case ECEPanelKind::Settings:
        default:
            return BuildTitledPanel(NSLOCTEXT("CE", "PlaceholderPanel", "Panel"));
    }
}

/* ---------- Actions ---------- */

FReply SCEVisualizer::OnOpenSummary()     { ShowPanel(ECEPanelKind::Summary);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenEcosystems()  { ShowPanel(ECEPanelKind::Ecosystems);  return FReply::Handled(); }
FReply SCEVisualizer::OnOpenBiomes()      { ShowPanel(ECEPanelKind::Biomes);      return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSpecies()     { ShowPanel(ECEPanelKind::Species);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenResources()   { ShowPanel(ECEPanelKind::Resources);   return FReply::Handled(); }
FReply SCEVisualizer::OnOpenWeather()     { ShowPanel(ECEPanelKind::Weather);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSimulations() { ShowPanel(ECEPanelKind::Simulations); return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSettings()    { ShowPanel(ECEPanelKind::Settings);    return FReply::Handled(); }
