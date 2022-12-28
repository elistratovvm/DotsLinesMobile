// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSphere.h"

#include "MobileGameElistratov/GameState/MobileGameStateBase.h"
#include "MobileGameElistratov/PlayerController/MobileGamePlayerController.h"

AGameSphere::AGameSphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");

	SphereMesh->OnInputTouchBegin.AddDynamic(this, &AGameSphere::InputTouchBeginResponse);
	SphereMesh->OnInputTouchEnd.AddDynamic(this, &AGameSphere::InputTouchEndResponse);
	RootComponent = SphereMesh;
}

void AGameSphere::Destroyed()
{
	Super::Destroyed();
	
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if(GameState)
	{
		if (bIsTouchBegin && bIsTouchEnd)
		{
			GameState->AddCurrentScore(MaxScore * CurrentScore);
		}
		else
		{
			GameState->DecreaseHealthPoint();
		}

		GameState->DecreaseQuantityElement();
	}
}

void AGameSphere::InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	bIsTouchBegin = true;
	
	FVector VectorLocation;
	FVector VectorDirection;
	AMobileGamePlayerController* PlayerController =
		Cast<AMobileGamePlayerController>(GetWorld()->GetFirstPlayerController());
	
	PlayerController->DeprojectMousePositionToWorld(VectorLocation, VectorDirection);

	if (PlayerController->bIsGameVibrateOn)
	{
		PlayerController->ClientPlayForceFeedback(MobileForceFeedbackEffect);
	}

	CurrentScore = 1.f - sqrt(
		(GetActorLocation().X - VectorLocation.X) * (GetActorLocation().X - VectorLocation.X)
		+ (GetActorLocation().Y - VectorLocation.Y) * (GetActorLocation().Y - VectorLocation.Y)) / sqrt(2.f) / 100.f;
}

void AGameSphere::InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	if (bIsTouchBegin)
	{
		bIsTouchEnd = true;
		Destroy();
	}
}
