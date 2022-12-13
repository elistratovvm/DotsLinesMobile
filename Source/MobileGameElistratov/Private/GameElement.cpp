// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElement.h"

// Sets default values
AGameElement::AGameElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsTouched = false;
}

// Called when the game starts or when spawned
void AGameElement::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void AGameElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameElement::Destroyed()
{
	if (bIsTouched)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Dead from touch!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Dead from time!"));
	}
	Super::Destroyed();
}

void AGameElement::TouchResponse()
{
	bIsTouched = true;
	Destroy();
}
