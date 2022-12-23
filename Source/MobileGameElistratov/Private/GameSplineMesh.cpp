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

// Called when the game starts or when spawned
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
			LineProgress = DistanceToSecondDot/Length;
		}
		else
		{
			LineProgress = DistanceToFirstDot/Length;
		}
		
		CurrentScore += 1.f - (DistanceToFirstDot + DistanceToSecondDot - Length) / 22.5f;
		NumberOfTicks++;

		GEngine->AddOnScreenDebugMessage(-1, 1.f/60.f, FColor::Green,
		FString::Printf(TEXT("%f, %f, %f, %f, %f, %f, %f"),
			CurrentScore / NumberOfTicks,
			VectorLocation.X, VectorLocation.Y,
			DistanceToFirstDot + DistanceToSecondDot - Length,
			DistanceToFirstDot, DistanceToSecondDot, 
			LineProgress));
	}
}

void AGameSplineMesh::Destroyed()
{
	Super::Destroyed();
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if (bIsTouchBegin && LineManager->bIsTouchBegin)
	{
		GameState->AddCurrentScore(MaxScore * LineProgress * CurrentScore / NumberOfTicks);
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
