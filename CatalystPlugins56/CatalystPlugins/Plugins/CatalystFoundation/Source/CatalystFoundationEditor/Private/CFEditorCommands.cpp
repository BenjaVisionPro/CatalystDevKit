// ============================================================================
// CFEditorCommands.cpp
// ============================================================================

#include "CFEditorCommands.h"

#define LOCTEXT_NAMESPACE "CFEditorCommands"

void FCFEditorCommands::RegisterCommands()
{
	UI_COMMAND(ExportAsJson,  "Export as JSON…",  "Export the current model to a JSON file.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ReloadDevJson, "Reload Dev JSON", "Reload Saved/<Plugin>/Model.json (if present).", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE