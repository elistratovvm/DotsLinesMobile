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
	bIsTouchBegin = true;
	LineManager->DotStartBeginTouch();
}

void AGameDotStart::InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if(!bIsTouchBegin)
	{
		LineManager->DotStartEndTouch();
	}
}

void AGameDotStart::EnterResponse()
{
	LineManager->EnterTouch();
}

void AGameDotStart::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	LineManager->LeaveTouch(TouchedComponent);
}
