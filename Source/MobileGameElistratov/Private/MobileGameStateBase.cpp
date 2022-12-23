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
	CurrentHealthPoint -= 1;
	CurrentHealthPoint = FMath::Clamp(CurrentHealthPoint, 0, 5);
	
	if(CurrentHealthPoint == 0)
	{
		if(GameOver.IsBound())
		{
			GameOver.Broadcast();
		}
	}
}

void AMobileGameStateBase::WinGameOver()
{
	if(GameOver.IsBound())
	{
		GameOver.Broadcast();
	}
}
