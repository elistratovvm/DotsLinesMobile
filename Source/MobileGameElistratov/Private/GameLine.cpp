// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLine.h"
#include "GameDot.h"
#include "GameDotStart.h"
#include "GameSplineMesh.h"
#include "MobileGameStateBase.h"

void AGameLine::BeginPlay()
{
	Super::BeginPlay();
}

void AGameLine::Destroyed()
{
	Super::Destroyed();
	
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if (bIsTouchBegin)
	{
		GameState->AddCurrentScore(MaxScore);
	}
	else
	{
		GameState->DecreaseHealthPoint();
	}
}

void AGameLine::DotStartBeginTouch()
{
	bOnTheLine = true;
	bIsTouchBegin = true;
}

void AGameLine::DotStartEndTouch()
{
	if (bOnTheLine)
	{
		bOnTheLine = false;
		DestroyLine();
	}
}


void AGameLine::DotEnterTouch()
{
	bOnDot = true;
	EnterTouch();
}

void AGameLine::DotLeaveTouch(UPrimitiveComponent* TouchedComponent)
{
	bOnDot = false;
	LeaveTouch(TouchedComponent);
}

void AGameLine::SplineMeshLeaveTouch(UPrimitiveComponent* TouchedComponent)
{
	LeaveTouch(TouchedComponent);
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
	}
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AGameLine::DestroyLine, 0.02f, false);
}

void AGameLine::DestroyLine()
{
	if(!bIsTouchBegin || bOnTheLine)
	{
		return;
	}
	
	for (AGameDotStart* Dot : DotsStart)
	{
		Dot->Destroy();
	}
	for (AGameDot* Dot : Dots)
	{
		Dot->Destroy();
	}
	for (AGameSplineMesh* Spline : Splines)
	{
		Spline->Destroy();
	}

	GetWorldTimerManager().ClearTimer(DeathTimer);
	Destroy();
}

#if WITH_EDITOR
void AGameLine::PrintText() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Elements Number: %i"), DotsStart.Num() + Dots.Num() + Splines.Num()));
}
#endif