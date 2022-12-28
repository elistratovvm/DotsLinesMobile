// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSplineMesh.h"

#include "GameLine.h"
#include "Components/SplineMeshComponent.h"
#include "MobileGameElistratov/GameState/MobileGameStateBase.h"
#include "MobileGameElistratov/PlayerController/MobileGamePlayerController.h"

AGameSplineMesh::AGameSplineMesh()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Game Spline Mesh Component"));
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SplineMeshComponent->SetCollisionProfileName("BlockAll");
	
	SplineMeshComponent->OnInputTouchEnter.AddDynamic(this, &AGameSplineMesh::InputTouchEnterResponse);
	SplineMeshComponent->OnInputTouchLeave.AddDynamic(this, &AGameSplineMesh::InputTouchLeaveResponse);
	RootComponent = SplineMeshComponent;
}

void AGameSplineMesh::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<AMobileGamePlayerController>(GetWorld()->GetFirstPlayerController());
}

void AGameSplineMesh::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsTouchBegin && LineObject->bIsTouchBegin && !bIsTouchEnd)
	{
		PlayerController->DeprojectMousePositionToWorld(VectorLocation, VectorDirection);
		
		DistanceToFirstDot = GetDistance(GetActorLocation(), VectorLocation);
		DistanceToSecondDot = GetDistance(LocationSecondDot, VectorLocation);
		
		if (bIsReverse)
		{
			if (LineProgress < DistanceToSecondDot/Length)
			{
				if (PlayerController->bIsGameVibrateOn)
				{
					PlayerController->ClientPlayForceFeedback(MobileForceFeedbackEffect);
				}
				
				LineProgress = DistanceToSecondDot/Length;
			}
		}
		else
		{
			if (LineProgress < DistanceToFirstDot/Length)
			{
				if (PlayerController->bIsGameVibrateOn)
				{
					PlayerController->ClientPlayForceFeedback(MobileForceFeedbackEffect);
				}
				
				LineProgress = DistanceToFirstDot/Length;
			}
		}
		
		ScorePercent += 1.f - (DistanceToFirstDot + DistanceToSecondDot - Length) / 22.5f;
		QuantityOfTicks++;
	}
}

void AGameSplineMesh::Destroyed()
{
	Super::Destroyed();
	
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());

	if(GameState)
	{
		if (bIsTouchBegin && LineObject->bIsTouchBegin)
		{
			GameState->AddCurrentScore(MaxScore * LineProgress * ScorePercent / QuantityOfTicks);
		}
	}
}

void AGameSplineMesh::InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if (LineObject->bIsTouchBegin)
	{
		bIsTouchBegin = true;
		
		PlayerController->DeprojectMousePositionToWorld(VectorLocation, VectorDirection);
		DistanceToFirstDot = GetDistance(GetActorLocation(), VectorLocation);
		DistanceToSecondDot = GetDistance(LocationSecondDot, VectorLocation);
		
		if (DistanceToSecondDot < DistanceToFirstDot)
		{
			bIsReverse = true;
		}

		LineObject->EnterTouch();
	}
}

void AGameSplineMesh::InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if (bIsTouchBegin && LineObject->bIsTouchBegin)
	{
		if (LineProgress > 0.75f)
		{
			LineProgress = 1.f;
		}
		bIsTouchEnd = true;
		
		LineObject->LeaveTouch(TouchedComponent);
	}
}

float AGameSplineMesh::GetDistance(FVector FirstDot, FVector SecondDot) const
{
	return sqrt((FirstDot.X - SecondDot.X) * (FirstDot.X - SecondDot.X)
			+ (FirstDot.Y - SecondDot.Y) * (FirstDot.Y - SecondDot.Y));
}
