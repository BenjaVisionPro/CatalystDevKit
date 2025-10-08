// ============================================
// Copyright © 2022 Jupiter Jones & BenjaVision
// All rights and remedies reserved
// ============================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CEEditorStyle.h"

class FCEEditorCommands : public TCommands<FCEEditorCommands>
{
public:

	FCEEditorCommands()
		: TCommands<FCEEditorCommands>(TEXT("CatalystEcosystemEditor"), NSLOCTEXT("Contexts", "CatalystEcosystemEditor", "CatalystEcosystemEditor Plugin"), NAME_None, FCEEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};