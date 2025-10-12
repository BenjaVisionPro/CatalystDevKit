// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CLEditorStyle.h"

class FCLEditorCommands : public TCommands<FCLEditorCommands>
{
public:

	FCLEditorCommands()
		: TCommands<FCLEditorCommands>(TEXT("CatalystLandformEditor"), NSLOCTEXT("Contexts", "CatalystLandformEditor", "CatalystLandformEditor Plugin"), NAME_None, FCLEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};