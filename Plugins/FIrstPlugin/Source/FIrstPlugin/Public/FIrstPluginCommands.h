// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FIrstPluginStyle.h"

class FFIrstPluginCommands : public TCommands<FFIrstPluginCommands>
{
public:

	FFIrstPluginCommands()
		: TCommands<FFIrstPluginCommands>(TEXT("FIrstPlugin"), NSLOCTEXT("Contexts", "FIrstPlugin", "FIrstPlugin Plugin"), NAME_None, FFIrstPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};