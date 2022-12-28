// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDotStart.h"

#include "GameLine.h"
#include "MobileGameElistratov/PlayerController/MobileGamePlayerController.h"

AGameDotStart::AGameDotStart()
{
	SphereMesh->OnInputTouchBegin.AddDynamic(this, &AGameDotStart::InputTouchBeginResponse);
	SphereMesh->OnInputTouchEnd.AddDynamic(this, &AGameDotStart::InputTouchEndResponse);
}

void AGameDotStart::InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	AMobileGamePlayerController* PlayerController =
			Cast<AMobileGamePlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerController->bIsGameVibrateOn)
	{
		PlayerController->ClientPlayForceFeedback(MobileForceFeedbackEffect);
	}
	
	bIsTouchBegin = true;
	LineObject->DotStartBeginTouch();
}

void AGameDotStart::InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if(!bIsTouchBegin)
	{
		LineObject->DotStartEndTouch();
	}
}

void AGameDotStart::EnterResponse()
{
	LineObject->EnterTouch();
}

void AGameDotStart::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	LineObject->LeaveTouch(TouchedComponent);
}
