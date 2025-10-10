// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CCEditorCommands.h"

#define LOCTEXT_NAMESPACE "FCCEditorModule"

void FCCEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Designer", "Bring up Catalyst:Connect Designer window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
