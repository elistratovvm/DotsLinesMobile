// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLine.h"
#include "MobileGameStateBase.h"

void AGameLine::Destroyed()
{
	Super::Destroyed();
	
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if(GameState)
	{
		GameState->DecreaseQuantityElement();
	
		if (bIsTouchBegin)
		{
			GameState->AddCurrentScore(MaxScore);
		}
		else
		{
			GameState->DecreaseHealthPoint();
		}
	}
}

void AGameLine::DotStartBeginTouch()
{
	bOnTheLine = true;
	bIsTouchBegin = true;
}

void AGameLine::DotStartEndTouch()
{
	bOnTheLine = false;
	
	if (bIsTouchBegin)
	{
		DestroyLine();
	}
}

void AGameLine::EnterTouch()
{
	bOnTheLine = true;
}

void AGameLine::LeaveTouch(UPrimitiveComponent* TouchedComponent)
{
	bOnTheLine = false;
	
	if(bIsTouchBegin)
	{
		TouchedComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(DeathTimer, this, &AGameLine::DestroyLine, 0.02f, false);
	}
}

void AGameLine::DestroyLine()
{
	if(bOnTheLine)
	{
		return;
	}

	for (AGameElement* Element: LineElements)
	{
		Element->Destroy();
	}

	GetWorldTimerManager().ClearTimer(DeathTimer);
	Destroy();
}