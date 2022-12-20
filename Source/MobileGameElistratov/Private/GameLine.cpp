// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLine.h"
#include "GameDot.h"
#include "GameDotStart.h"
#include "GameSplineMesh.h"

void AGameLine::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
} 

void AGameLine::PrintText() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Elements Number: %i"), DotsStart.Num() + Dots.Num() + Splines.Num()));
}

void AGameLine::Destroyed()
{
	//Debug method, delete after development will be completed
	//------------------------------------------------------------------------------------------------------------------
	if (bIsTouched)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Line being touched!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Line dead from time!"));
	}
	//------------------------------------------------------------------------------------------------------------------
	Super::Destroyed();
}

void AGameLine::DotStartBeginTouch()
{
	bOnTheLine = true;
	bIsLineStarted = true;
}

void AGameLine::DotStartEndTouch()
{
	if (bOnTheLine)
	{
		bOnTheLine = false;
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
	if(bIsLineStarted)
	{
		TouchedComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AGameLine::DestroyLine, 0.02f, false);
}

void AGameLine::DestroyLine()
{
	if(!bIsLineStarted)
	{
		return;
	}
	if (bOnTheLine)
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
