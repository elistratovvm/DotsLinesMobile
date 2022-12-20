// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "GameElement.h"
#include "GameSpawner.h"
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
	
	if (!Overlay_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Overlay class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!Spawner_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Spawner class. Did you make assigment on Blueprint?"));
		return;
	}
	Overlay = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), Overlay_Class);
	Overlay->AddToViewport(0);
	Spawner = GetWorld()->SpawnActor<AGameSpawner>(Spawner_Class);
}

void AGameManager::SpawnLevel(const UDataTable* FGameTableDots) const
{
	Spawner->ReadAndSpawn(FGameTableDots);
}

void AGameManager::DeleteSpawnActors()
{
	TArray<AGameElement*> Elements = Spawner->GetSpawnElements();
	for (AGameElement* Actor : Elements)
	{
		Actor->Destroy();
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

