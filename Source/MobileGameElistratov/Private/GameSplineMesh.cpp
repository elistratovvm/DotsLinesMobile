// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSplineMesh.h"

#include "GameLine.h"
#include "MobileGameStateBase.h"
#include "Components/SplineMeshComponent.h"

AGameSplineMesh::AGameSplineMesh()
{
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
	PlayerController = GetWorld()->GetFirstPlayerController();
}

void AGameSplineMesh::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsTouchBegin && LineManager->bIsTouchBegin && !bIsTouchEnd)
	{
		PlayerController->DeprojectMousePositionToWorld(VectorLocation, VectorDirection);

		DistanceToFirstDot = GetDistance(GetActorLocation(), VectorLocation);
		DistanceToSecondDot = GetDistance(ActorSecondDot, VectorLocation);
		
		if (bIsReverse)
		{
			if (LineProgress < DistanceToSecondDot/Length)
			{
				LineProgress = DistanceToSecondDot/Length;
			}
		}
		else
		{
			if (LineProgress < DistanceToFirstDot/Length)
			{
				LineProgress = DistanceToFirstDot/Length;
			}
		}
		
		CurrentScore += 1.f - (DistanceToFirstDot + DistanceToSecondDot - Length) / 22.5f;
		NumberOfTicks++;
	}
}

void AGameSplineMesh::Destroyed()
{
	Super::Destroyed();
	
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());

	if(GameState)
	{
		if (bIsTouchBegin && LineManager->bIsTouchBegin)
		{
			GameState->AddCurrentScore(MaxScore * LineProgress * CurrentScore / NumberOfTicks);
		}
	}
}

void AGameSplineMesh::InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if (LineManager->bIsTouchBegin)
	{
		bIsTouchBegin = true;
		
		PlayerController->DeprojectMousePositionToWorld(VectorLocation, VectorDirection);
		DistanceToFirstDot = GetDistance(GetActorLocation(), VectorLocation);
		DistanceToSecondDot = GetDistance(ActorSecondDot, VectorLocation);
		
		if (DistanceToSecondDot < DistanceToFirstDot)
		{
			bIsReverse = true;
		}

		LineManager->EnterTouch();
	}
}

void AGameSplineMesh::InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if (bIsTouchBegin && LineManager->bIsTouchBegin)
	{
		if (LineProgress > 0.8f)
		{
			LineProgress = 1.f;
		}
		bIsTouchEnd = true;
		
		LineManager->SplineMeshLeaveTouch(TouchedComponent);
	}
}

float AGameSplineMesh::GetDistance(FVector FirstDot, FVector SecondDot) const
{
	return sqrt((FirstDot.X - SecondDot.X) * (FirstDot.X - SecondDot.X)
			+ (FirstDot.Y - SecondDot.Y) * (FirstDot.Y - SecondDot.Y));
}
