// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDot.h"
#include "GameLine.h"
#include "MobileGamePlayerController.h"
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
		if (bIsTouchBegin && LineObject->bIsTouchBegin)
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
	if(LineObject->bIsTouchBegin)
	{
		AMobileGamePlayerController* PlayerController =
			Cast<AMobileGamePlayerController>(GetWorld()->GetFirstPlayerController());

		if (PlayerController->bIsGameVibrateOn)
		{
			PlayerController->ClientPlayForceFeedback(MobileForceFeedbackEffect);
		}
		
		bIsTouchBegin = true;
		LineObject->EnterTouch();
	}
}

void AGameDot::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	if (bIsTouchBegin)
	{
		LineObject->LeaveTouch(TouchedComponent);
	}
}
