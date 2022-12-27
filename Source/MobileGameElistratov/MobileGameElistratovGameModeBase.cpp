// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileGameElistratovGameModeBase.h"
#include "MobileGamePlayerController.h"
#include "Actors/Non-interactive/GameManager.h"

AMobileGameElistratovGameModeBase::AMobileGameElistratovGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMobileGamePlayerController::StaticClass();
}

void AMobileGameElistratovGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameManager_BP = GetWorld()->SpawnActor<AGameManager>(GameManager);
}