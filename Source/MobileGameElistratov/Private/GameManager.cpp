// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "GameElement.h"
#include "GameSpawner.h"
#include "MobileGameStateBase.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Overlay class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!SpawnerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Spawner class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!GameOverWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Game Over Widget class. Did you make assigment on Blueprint?"));
		return;
	}
	CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass)->AddToViewport(0);
	Spawner = GetWorld()->SpawnActor<AGameSpawner>(SpawnerClass);

	AMobileGameStateBase* GameState = Cast<AMobileGameStateBase>(GetWorld()->GetGameState());
	GameState->GameOver.AddDynamic(this, &AGameManager::GameOverDelegateFunction);
}

void AGameManager::RemoveFromSpawnArray(AGameElement* GameActor) const
{
	Spawner->RemoveOneElement(GameActor);
}

void AGameManager::SpawnLevel(const UDataTable* FGameTableDots)
{
	const float MaxTime = Spawner->SpawnAndGetLevelTime(FGameTableDots);
	FTimerHandle LocalSpawnTimer;
	GetWorldTimerManager().SetTimer(LocalSpawnTimer, this, &AGameManager::GameOverDelegateFunction, MaxTime + 0.000001f, false);
}

void AGameManager::DeleteSpawnActors()
{
	GetWorldTimerManager().ClearAllTimersForObject(Spawner);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	
	Spawner->DestroyAllElements();
}

void AGameManager::GameOverDelegateFunction()
{
	CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), GameOverWidgetClass)->AddToViewport(0);
	DeleteSpawnActors();
}
