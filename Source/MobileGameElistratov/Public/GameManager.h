// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class UDataTable;
class AGameSpawner;
class AGameElement;

UCLASS()
class MOBILEGAMEELISTRATOV_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AGameSpawner> SpawnerClass;

	
	void RemoveFromSpawnArray(AGameElement* GameActor) const;

	
	UFUNCTION(BlueprintCallable)
	void SpawnLevel(const UDataTable* FGameTableDots);
	
	UFUNCTION(BlueprintCallable)
	void DeleteSpawnActors();
	
	UFUNCTION()
	void GameOverDelegateFunction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AGameSpawner* Spawner;
};
