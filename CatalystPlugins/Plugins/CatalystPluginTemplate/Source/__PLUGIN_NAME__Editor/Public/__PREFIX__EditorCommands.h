// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "__PREFIX__EditorStyle.h"

class F__PREFIX__EditorCommands : public TCommands<F__PREFIX__EditorCommands>
{
public:

	F__PREFIX__EditorCommands()
		: TCommands<F__PREFIX__EditorCommands>(TEXT("__PLUGIN_NAME__Editor"), NSLOCTEXT("Contexts", "__PLUGIN_NAME__Editor", "__PLUGIN_NAME__Editor Plugin"), NAME_None, F__PREFIX__EditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};