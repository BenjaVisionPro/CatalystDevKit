// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CEEditorCommands.h"

#define LOCTEXT_NAMESPACE "FCEEditorModule"

void FCEEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Ecosystem", "Bring up Catalyst:Ecosystem Designer window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
