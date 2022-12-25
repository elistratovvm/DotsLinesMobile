// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "GameSpawner.h"
#include "MobileGameHUD.h"
#include "MobileGameStateBase.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SpawnerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Spawner class. Did you make assigment on Blueprint?"));
		return;
	}
	
	Spawner = GetWorld()->SpawnActor<AGameSpawner>(SpawnerClass);

	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if(GameState)
	{
		GameState->GameOver.AddDynamic(this, &AGameManager::GameOverDelegateFunction);
	}
}

void AGameManager::RemoveFromSpawnArray(AGameElement* GameActor) const
{
	Spawner->RemoveOneElement(GameActor);
}

void AGameManager::SpawnLevel(const UDataTable* FGameTableDots)
{
	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if(GameState)
	{
		GameState->QuantityElementForGame = Spawner->SpawnAndGetQuantityElements(FGameTableDots);
	}
}

void AGameManager::DeleteSpawnActors()
{
	GetWorldTimerManager().ClearAllTimersForObject(Spawner);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	
	Spawner->DestroyAllElements();
}

void AGameManager::GameOverDelegateFunction()
{
	AMobileGameHUD* GameHUD = Cast<AMobileGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (GameHUD)
	{
		GameHUD->ChangeCurrentWidget(EGameState::GameOver);
	}
	
	DeleteSpawnActors();
}
