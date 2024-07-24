// Copyright Epic Games, Inc. All Rights Reserved.

#include "FIrstPluginCommands.h"

#define LOCTEXT_NAMESPACE "FFIrstPluginModule"

void FFIrstPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FIrstPlugin", "Bring up FIrstPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
