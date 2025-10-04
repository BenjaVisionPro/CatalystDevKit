// ============================================
// Catalyst : Ecosystem Visualizer (Dashboard)
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Styling/SlateBrush.h"

enum class ECEPanelKind : uint8
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

/**
 * Icon-first dashboard. It shows quick counts pulled from the live model
 * and routes to the different panels. No hidden magic here.
 */
class SCEVisualizer : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCEVisualizer) {}
		SLATE_ARGUMENT(int32, Seed) // kept for API compat; not used
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// ---- Tile builder (small self-contained helper) ----
	TSharedRef<SWidget> MakeIconTile(
		const TCHAR* Glyph,                 // FA glyph, e.g. TEXT("\uf0ac")
		TOptional<int32> Count,             // optional badge count (top-right)
		const FLinearColor StatusColor,     // status dot (bottom-right)
		FOnClicked OnClicked                // action
	);

	// ---- Panel plumbing ----
	void                ShowPanel(ECEPanelKind Kind);
	TSharedRef<SWidget> BuildPanel(ECEPanelKind Kind);
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

	// ---- Model snapshot ----
	// We grab a fresh snapshot during Construct. If the service later swaps
	// the live model, we’ll add a notification hook and refresh these numbers.
	void RefreshCountsFromModel(); // cheap counts; no caching needed

private:
	// Numbers shown on the tiles
	int32 EcosystemCount = 0;
	int32 BiomeCount     = 0;
	int32 SpeciesCount   = 0;
	int32 ResourceCount  = 0;

	int32 PreviewSeed    = 0;

	// Panel host + cache
	TSharedPtr<class SBox>             PanelHost;
	TMap<ECEPanelKind, TWeakPtr<SWidget>> PanelCache;
	ECEPanelKind                       ActivePanel = ECEPanelKind::None;
};