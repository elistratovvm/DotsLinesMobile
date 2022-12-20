// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSphere.h"

AGameSphere::AGameSphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");

	SphereMesh->OnInputTouchBegin.AddDynamic(this, &AGameSphere::InputTouchBeginResponse);
	SphereMesh->OnInputTouchEnd.AddDynamic(this, &AGameSphere::InputTouchEndResponse);
}

void AGameSphere::BeginPlay()
{
	Super::BeginPlay();
}

void AGameSphere::InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Sphere Touch Begin!"));
	bIsTouched = true;
}

void AGameSphere::InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Sphere Touch End!"));
	
	if (bIsTouched)
	{
		Destroy();
	}
}
