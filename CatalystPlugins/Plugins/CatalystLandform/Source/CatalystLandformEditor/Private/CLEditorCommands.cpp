// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#include "CLEditorCommands.h"

#define LOCTEXT_NAMESPACE "FCLEditorModule"

void FCLEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Landform", "Bring up Catalyst:Landform Designer window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
