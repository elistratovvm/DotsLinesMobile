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
	CurrentHealthPoint = FMath::Clamp(CurrentHealthPoint, 0, MaxHealthPoint);
	
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
	if(GameOver.IsBound())
	{
		GameOver.Broadcast();
	}
}
