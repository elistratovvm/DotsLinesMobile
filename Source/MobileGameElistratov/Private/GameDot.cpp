// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDot.h"
#include "GameLine.h"
#include "MobileGameStateBase.h"

AGameDot::AGameDot()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");
	
	SphereMesh->OnInputTouchEnter.AddDynamic(this, &AGameDot::InputTouchEnterResponse);
	SphereMesh->OnInputTouchLeave.AddDynamic(this, &AGameDot::InputTouchLeaveResponse);
	RootComponent = SphereMesh;
}

void AGameDot::Destroyed()
{
	Super::Destroyed();

	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());

	if(GameState)
	{
		if (bIsTouchBegin && LineManager->bIsTouchBegin)
		{
			GameState->AddCurrentScore(MaxScore);
		}
	}
}

void AGameDot::InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	EnterResponse();
}

void AGameDot::InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	LeaveResponse(TouchedComponent);
}

void AGameDot::EnterResponse()
{
	bIsTouchBegin = true;
	LineManager->DotEnterTouch();
}

void AGameDot::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	if (bIsTouchBegin && LineManager->bIsTouchBegin)
	{
		LineManager->DotLeaveTouch(TouchedComponent);
	}
}
