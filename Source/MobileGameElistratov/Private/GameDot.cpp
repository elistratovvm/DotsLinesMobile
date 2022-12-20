// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDot.h"
#include "GameLine.h"

AGameDot::AGameDot()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");
	
	SphereMesh->OnInputTouchEnter.AddDynamic(this, &AGameDot::InputTouchEnterResponse);
	SphereMesh->OnInputTouchLeave.AddDynamic(this, &AGameDot::InputTouchLeaveResponse);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Dot Touch Enter!"));
	LineManager->EnterTouch();
}

void AGameDot::LeaveResponse(UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dot Touch Leave!"));
	LineManager->LeaveTouch(TouchedComponent);
}

