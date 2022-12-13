// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileGameElistratovGameModeBase.h"
#include "MobileGamePlayerController.h"

AMobileGameElistratovGameModeBase::AMobileGameElistratovGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMobileGamePlayerController::StaticClass();
}