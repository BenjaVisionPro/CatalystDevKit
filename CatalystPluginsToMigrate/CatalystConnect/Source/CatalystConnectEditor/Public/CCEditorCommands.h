// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CCEditorStyle.h"

class FCCEditorCommands : public TCommands<FCCEditorCommands>
{
public:

	FCCEditorCommands()
		: TCommands<FCCEditorCommands>(TEXT("CatalystConnectEditor"), NSLOCTEXT("Contexts", "CatalystConnectEditor", "CatalystConnectEditor Plugin"), NAME_None, FCCEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};