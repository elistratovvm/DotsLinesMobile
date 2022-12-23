// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElement.h"

#include "GameManager.h"
#include "MobileGameElistratov/MobileGameElistratovGameModeBase.h"

AGameElement::AGameElement()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsTouchBegin = false;
}

void AGameElement::BeginDestroy()
{
	Super::BeginDestroy();
	if (GetWorld())
	{
		AMobileGameElistratovGameModeBase* GameMod = Cast<AMobileGameElistratovGameModeBase>(GetWorld()->GetAuthGameMode());
		AGameManager* GameManager = GameMod->GameManager_BP;
		GameManager->RemoveFromSpawnArray(this);
	}
}

void AGameElement::Destroyed()
{
	Super::Destroyed();
	
}

void AGameElement::SetLifeTime(float LifeTime)
{
	SetLifeSpan(LifeTime);
}
