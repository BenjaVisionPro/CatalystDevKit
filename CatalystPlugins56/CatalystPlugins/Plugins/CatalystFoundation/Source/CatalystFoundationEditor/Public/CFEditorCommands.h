// ============================================================================
// CFEditorCommands.h — Shared editor-level actions for Foundation tools
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"

/**
 * Shared editor actions for all Foundation-based asset editors/toolkits.
 * E.g., used by FCFModelEditorToolkit to add Export/Reload buttons.
 */
class CATALYSTFOUNDATIONEDITOR_API FCFEditorCommands : public TCommands<FCFEditorCommands>
{
public:
	FCFEditorCommands()
		: TCommands<FCFEditorCommands>(
			TEXT("CFEditorCommands"),
			NSLOCTEXT("CFEditor", "CommandsCtx", "Catalyst Foundation"),
			NAME_None,
			FAppStyle::GetAppStyleSetName())
	{}

	virtual void RegisterCommands() override;

	// --- Actions ---
	TSharedPtr<FUICommandInfo> ExportAsJson;   // “Export as JSON…”
	TSharedPtr<FUICommandInfo> ReloadDevJson;  // “Reload Dev JSON”
};