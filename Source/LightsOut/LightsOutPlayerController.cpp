// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LightsOut.h"
#include "LightsOutPlayerController.h"

ALightsOutPlayerController::ALightsOutPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
