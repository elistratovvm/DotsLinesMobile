// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElement.h"

#include "MobileGameElistratov/MobileGameElistratovGameModeBase.h"
#include "MobileGameElistratov/Actors/Non-interactive/Manager/GameManager.h"

void AGameElement::BeginDestroy()
{
	Super::BeginDestroy();
	
	if(GetWorld())
	{
		AMobileGameElistratovGameModeBase* GameMod = Cast<AMobileGameElistratovGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMod)
		{
			AGameManager* GameManager = GameMod->GameManager_BP;
			if(GameManager)
			{
				GameManager->RemoveFromSpawnArray(this);
			}
		}
	}
}
