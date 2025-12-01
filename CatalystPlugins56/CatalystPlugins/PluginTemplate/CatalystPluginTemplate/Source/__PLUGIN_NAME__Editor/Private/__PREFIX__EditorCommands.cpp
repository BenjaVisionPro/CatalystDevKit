// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "__PREFIX__EditorCommands.h"

#define LOCTEXT_NAMESPACE "F__PREFIX__EditorModule"

void F__PREFIX__EditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "__PLUGIN_DISPLAY_NAME__", "Bring up Catalyst:__PLUGIN_DISPLAY_NAME__ Designer window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
