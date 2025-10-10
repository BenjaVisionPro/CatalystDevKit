// ============================================
// Catalyst:Ecosystem Visualizer (Dashboard)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Styling/SlateBrush.h"

enum class E__PREFIX__PanelKind : uint8
{
    None = 0,
    Summary,
    Ecosystems,
    Biomes,
    Species,
    Resources,
    Weather,
    Simulations,
    Settings,
};

/** Catalyst:Ecosystem Dashboard (icon-first, responsive) */
class SCEVisualizer : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCEVisualizer) {}
        SLATE_ARGUMENT(int32, Seed) // kept for API compat
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    // ---- Tile builder ----
    TSharedRef<SWidget> MakeIconTile(
        const TCHAR* Glyph,                // FA glyph, e.g. TEXT("\uf0ac")
        TOptional<int32> Count,            // optional badge count (top-right)
        const FLinearColor StatusColor,    // status dot (bottom-right)
        FOnClicked OnClicked               // action
    );

    // ---- Panel plumbing ----
    void ShowPanel(E__PREFIX__PanelKind Kind);
    TSharedRef<SWidget> BuildPanel(E__PREFIX__PanelKind Kind);
    TSharedRef<SWidget> BuildTitledPanel(const FText& Title);

    // ---- Actions (hook up real behavior) ----
    FReply OnOpenSummary();
    FReply OnOpenEcosystems();
    FReply OnOpenBiomes();
    FReply OnOpenSpecies();
    FReply OnOpenResources();
    FReply OnOpenWeather();
    FReply OnOpenSimulations();
    FReply OnOpenSettings();

private:
    int32 PreviewSeed = 0;

    // Panel host + cache
    TSharedPtr<class SBox> PanelHost;
    TMap<E__PREFIX__PanelKind, TWeakPtr<SWidget>> PanelCache;
    E__PREFIX__PanelKind ActivePanel = E__PREFIX__PanelKind::None;
};