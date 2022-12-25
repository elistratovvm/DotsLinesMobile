// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileGameStateBase.h"

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
	CurrentHealthPoint = FMath::Clamp(CurrentHealthPoint, 0, 5);
	
	if(CurrentHealthPoint < 1)
	{
		CurrentHealthPoint = 0;
		
		if(GameOver.IsBound())
		{
			GameOver.Broadcast();
		}
	}
}

void AMobileGameStateBase::DecreaseQuantityElement()
{
	QuantityElementForGame--;

	if(QuantityElementForGame < 1)
	{
		WinGameOver();
	}
}

void AMobileGameStateBase::WinGameOver()
{
	if(GameOver.IsBound())
	{
		GameOver.Broadcast();
	}
}
