// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LightsOut.h"
#include "LightsOutGameMode.h"
#include "LightsOutPlayerController.h"

ALightsOutGameMode::ALightsOutGameMode()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = ALightsOutPlayerController::StaticClass();
}
