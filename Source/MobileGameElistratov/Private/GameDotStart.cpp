// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDotStart.h"

#include "GameLine.h"

AGameDotStart::AGameDotStart()
{
	SphereMesh->OnInputTouchBegin.AddDynamic(this, &AGameDotStart::InputTouchBeginResponse);
	SphereMesh->OnInputTouchEnd.AddDynamic(this, &AGameDotStart::InputTouchEndResponse);
}

void AGameDotStart::InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Dot Start Touch Begin!"));
	bIsTouched = true;
	LineManager->DotStartBeginTouch();
}

void AGameDotStart::InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Dot Start Touch End!"));
	if(!bIsTouched)
	{
		LineManager->DotStartEndTouch();
	}
}

void AGameDotStart::EnterResponse()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Dot Start Touch Enter!"));
	LineManager->EnterTouch();
}

void AGameDotStart::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dot Start Touch Leave!"));
	bIsTouched = false;
	LineManager->LeaveTouch(TouchedComponent);
}
