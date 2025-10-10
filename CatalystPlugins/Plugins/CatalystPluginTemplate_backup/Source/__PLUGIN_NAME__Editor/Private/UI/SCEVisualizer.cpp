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

#include "Styles/CFEditorFontsStyle.h"   // shared Font Awesome + Bebas
#include "__PREFIX__EditorStyle.h"               // plugin brushes (e.g. __PREFIX__.Logo64)
#include "UI/__PREFIX__FontAwesome.h"            // FA glyph constants
#include "UI/Panels/SCESummaryPanel.h"

// Runtime access to the data model
#include "Services/__PREFIX__ModelService.h"
#include "Model/__PREFIX__ModelAsset.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"

namespace
{
    // ---- Tile metrics ----
    constexpr float kTileHeight = 60.f;
    constexpr float kAspect     = 2.2f;                // width = height * aspect
    constexpr float kTileWidth  = kTileHeight * kAspect;
    const FMargin   kCardPad(14.f);

    // Font Awesome LIGHT icon at a target pixel size.
    TSharedRef<STextBlock> MakeFAIconLightSized(const TCHAR* Glyph, float PixelSize)
    {
        FSlateFontInfo IconFont = FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::IconLight24);
        IconFont.Size = PixelSize;
        return SNew(STextBlock).Font(IconFont).Text(FText::FromString(Glyph));
    }

    // 6px status dot (bottom-right on our tiles).
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

    // --- Minimal, editor-safe resolver for our service/model ---
    // Scans all world contexts (handles PIE/SIE) and returns the first CE service.
    static U__PREFIX__ModelService* ResolveService()
    {
        if (!GEngine) return nullptr;

        const TIndirectArray<FWorldContext>& Contexts = GEngine->GetWorldContexts();
        for (int32 i = 0; i < Contexts.Num(); ++i)
        {
            if (UGameInstance* GI = Contexts[i].OwningGameInstance)
            {
                if (U__PREFIX__ModelService* Svc = GI->GetSubsystem<U__PREFIX__ModelService>())
                {
                    return Svc;
                }
            }
        }
        return nullptr;
    }

    static const U__PREFIX__ModelAsset* ResolveModelAsset()
    {
        if (const U__PREFIX__ModelService* Svc = ResolveService())
        {
            return Svc->GetModelAsset();
        }
        return nullptr;
    }
}

/* ---------- Construct ---------- */

void SCEVisualizer::Construct(const FArguments& InArgs)
{
    // Keeping seed for API compatibility in case we surface it later.
    PreviewSeed = InArgs._Seed;

    const FLinearColor OK   = FLinearColor(0.12f, 0.80f, 0.32f);
    const FLinearColor WARN = FLinearColor(0.98f, 0.73f, 0.08f);
    const FLinearColor ERR  = FLinearColor(0.86f, 0.20f, 0.20f);
    const FLinearColor NEUT = FLinearColor(0.55f, 0.55f, 0.55f);

    // Pull counts directly from the live model. If the model isn't ready yet,
    // leave the badge hidden (optional remains unset).
    auto CountOrUnset = [](TFunctionRef<int32(const F__PREFIX__Model&)> Getter) -> TOptional<int32>
    {
        if (const U__PREFIX__ModelAsset* A = ResolveModelAsset())
        {
            return Getter(A->GetModel());
        }
        return TOptional<int32>(); // hide until the service seeds the model
    };

    const TOptional<int32> EcosystemCount = CountOrUnset([](const F__PREFIX__Model& M){ return M.Ecosystems.Num(); });
    const TOptional<int32> BiomeCount     = CountOrUnset([](const F__PREFIX__Model& M){ return M.Biomes.Num();     });
    const TOptional<int32> SpeciesCount   = CountOrUnset([](const F__PREFIX__Model& M){ return M.Animals.Num();    });
    const TOptional<int32> ResourceCount  = CountOrUnset([](const F__PREFIX__Model& M){ return M.Resources.Num();  });

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

                // Logo (click to jump back to Summary)
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
                        .Image(F__PREFIX__EditorStyle::Get().GetBrush("__PREFIX__.Logo64"))
                        .ToolTipText(NSLOCTEXT("CE", "DashTitle", "Catalyst: Summary / News"))
                    ]
                ]

                // Spacer
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(24.f, 0.f)
                [
                    SNullWidget::NullWidget
                ]

                // Tiles
                + SHorizontalBox::Slot()
                .FillWidth(1.f)
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
                    SNew(SHorizontalBox)

                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(__PREFIX__FA::Globe, TOptional<int32>(EcosystemCount), OK,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenEcosystems))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(__PREFIX__FA::Leaf, TOptional<int32>(BiomeCount), OK,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenBiomes))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(__PREFIX__FA::Paw, TOptional<int32>(SpeciesCount), OK,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenSpecies))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(__PREFIX__FA::Cubes, TOptional<int32>(ResourceCount), WARN,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenResources))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        // Weather not counted yet
                        MakeIconTile(__PREFIX__FA::CloudSun, TOptional<int32>(), NEUT,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenWeather))
                    ]
                    + SHorizontalBox::Slot().FillWidth(1.f/6.f).Padding(4.f,0.f)
                    [
                        MakeIconTile(__PREFIX__FA::SlidersH, TOptional<int32>(), OK,
                                     FOnClicked::CreateSP(this, &SCEVisualizer::OnOpenSimulations))
                    ]
                ]

                // Spacer
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(24.f, 0.f)
                [
                    SNullWidget::NullWidget
                ]

                // Settings (placeholder action)
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
                        MakeFAIconLightSized(__PREFIX__FA::Cog, 24.f)
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
    ShowPanel(E__PREFIX__PanelKind::Summary);
}

/* ---------- Tile builder ---------- */

TSharedRef<SWidget> SCEVisualizer::MakeIconTile(
    const TCHAR* Glyph,
    TOptional<int32> Count,
    const FLinearColor StatusColor,
    FOnClicked OnClicked)
{
    const float IconPx = FMath::Clamp((kTileHeight - (kCardPad.Top + kCardPad.Bottom)) * 0.72f, 18.f, 56.f);

    FSlateFontInfo CountFont = FCFEditorFontsStyle::Get().GetFontStyle(FCFEditorFontsStyle::BebasBold20);
    CountFont.Size = 18.f;

    return SNew(SButton)
        .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
        .ContentPadding(0.f)
        .OnClicked(OnClicked)
        [
            SNew(SBox)
            .WidthOverride(kTileWidth)
            .HeightOverride(kTileHeight)
            [
                SNew(SBorder)
                .Padding(kCardPad)
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                [
                    SNew(SOverlay)

                    // Left icon
                    + SOverlay::Slot()
                    .HAlign(HAlign_Left)
                    .VAlign(VAlign_Center)
                    [
                        MakeFAIconLightSized(Glyph, IconPx)
                    ]

                    // Right: number (optional) + status dot
                    + SOverlay::Slot()
                    .HAlign(HAlign_Right)
                    .VAlign(VAlign_Center)
                    [
                        SNew(SVerticalBox)

                        // Number (visible only if Count has a value)
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Center)
                        .Padding(FMargin(0.f, 0.f, 0.f, 4.f))
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

                        // Status dot
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

void SCEVisualizer::ShowPanel(E__PREFIX__PanelKind Kind)
{
    if (!PanelHost.IsValid() || ActivePanel == Kind)
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

    TSharedRef<SWidget> NewPanel = BuildPanel(Kind);
    PanelCache.Add(Kind, NewPanel);
    PanelHost->SetContent(NewPanel);
    ActivePanel = Kind;
}

TSharedRef<SWidget> SCEVisualizer::BuildTitledPanel(const FText& Title)
{
    // Simple scaffold panel; we’ll replace with real editors panel-by-panel.
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

TSharedRef<SWidget> SCEVisualizer::BuildPanel(E__PREFIX__PanelKind Kind)
{
    switch (Kind)
    {
        case E__PREFIX__PanelKind::Summary:
            return SNew(SCESummaryPanel).Title(NSLOCTEXT("CE", "SummaryPanel", "Summary / News"));

        // Placeholders until the concrete editors land
        case E__PREFIX__PanelKind::Ecosystems:
        case E__PREFIX__PanelKind::Biomes:
        case E__PREFIX__PanelKind::Species:
        case E__PREFIX__PanelKind::Resources:
        case E__PREFIX__PanelKind::Weather:
        case E__PREFIX__PanelKind::Simulations:
        case E__PREFIX__PanelKind::Settings:
        default:
            return BuildTitledPanel(NSLOCTEXT("CE", "PlaceholderPanel", "Panel"));
    }
}

/* ---------- Actions ---------- */

FReply SCEVisualizer::OnOpenSummary()     { ShowPanel(E__PREFIX__PanelKind::Summary);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenEcosystems()  { ShowPanel(E__PREFIX__PanelKind::Ecosystems);  return FReply::Handled(); }
FReply SCEVisualizer::OnOpenBiomes()      { ShowPanel(E__PREFIX__PanelKind::Biomes);      return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSpecies()     { ShowPanel(E__PREFIX__PanelKind::Species);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenResources()   { ShowPanel(E__PREFIX__PanelKind::Resources);   return FReply::Handled(); }
FReply SCEVisualizer::OnOpenWeather()     { ShowPanel(E__PREFIX__PanelKind::Weather);     return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSimulations() { ShowPanel(E__PREFIX__PanelKind::Simulations); return FReply::Handled(); }
FReply SCEVisualizer::OnOpenSettings()    { ShowPanel(E__PREFIX__PanelKind::Settings);    return FReply::Handled(); }