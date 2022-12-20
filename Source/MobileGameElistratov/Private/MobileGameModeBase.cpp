// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileGameModeBase.h"
#include "GameManager.h"

void AMobileGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameManager_BP = GetWorld()->SpawnActor<AGameManager>(GameManager);
}
