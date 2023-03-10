// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "../Spawner/GameSpawner.h"
#include "MobileGameElistratov/GameState/MobileGameStateBase.h"
#include "MobileGameElistratov/HUD/MobileGameHUD.h"

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

	GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	
	if(GameState)
	{
		GameState->GameOver.AddDynamic(this, &AGameManager::GameOverDelegateFunction);
	}
}

void AGameManager::RemoveFromSpawnArray(AGameElement* GameActor) const
{
	Spawner->RemoveOneElement(GameActor);
}

void AGameManager::SpawnLevelByIndex(const int Index)
{
	if(GameState)
	{
		if(DataTables[Index])
		{
			GameState->QuantityElementForGame = Spawner->SpawnAndGetQuantityElements(DataTables[Index]);
		}
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

	if (GameHUD && GameState)
	{
		if(GameState->CurrentHealthPoint == 0)
		{
			GameHUD->ChangeCurrentWidget(EGameState::GameOver);
		}
		else
		{
			GameHUD->ChangeCurrentWidget(EGameState::GameWin);
		}
	}
	
	DeleteSpawnActors();
}
