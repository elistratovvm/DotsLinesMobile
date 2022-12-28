// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileGameStateBase.h"

#include "GameFramework/GameSession.h"
#include "MobileGameElistratov/HUD/MobileGameHUD.h"
#include "MobileGameElistratov/PlayerController/MobileGamePlayerController.h"

float AMobileGameStateBase::GetCurrentScore()
{
	return CurrentScore;
}

void AMobileGameStateBase::ResetCurrentScore()
{
	CurrentScore = 0;
}

void AMobileGameStateBase::ResetCurrentHealth()
{
	CurrentHealthPoint = MaxHealthPoint;
}

void AMobileGameStateBase::AddCurrentScore(float AddedScore)
{
	CurrentScore += AddedScore;
}

void AMobileGameStateBase::DecreaseHealthPoint()
{
	CurrentHealthPoint--;
	
	if(CurrentHealthPoint == 0)
	{
		GameOverFunction();
	}
}

void AMobileGameStateBase::DecreaseQuantityElement()
{
	QuantityElementForGame--;

	if(QuantityElementForGame < 1)
	{
		GameOverFunction();
	}
}

void AMobileGameStateBase::GameOverFunction() const
{
	AMobileGamePlayerController* PlayerController =
		Cast<AMobileGamePlayerController>(GetWorld()->GetFirstPlayerController());

	if(PlayerController)
	{
		AMobileGameHUD* HUD = Cast<AMobileGameHUD>(PlayerController->GetHUD());
		
		if(GameOver.IsBound() && HUD->GetCurrentGameState() == PlayGame)
		{
			GameOver.Broadcast();
		}
	}
	
	
	
}
