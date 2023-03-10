// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class AGameSpawner;

/* Game manager linking spawner, widgets and game state */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:
	AGameManager();

	/** Subclass of spawner. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AGameSpawner> SpawnerClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UDataTable*> DataTables;
	
	void RemoveFromSpawnArray(class AGameElement* GameActor) const;

	/**
	 *	Spawn game elements from data table
	 *
	 *	@param Index		Index of element in Data Tables array
	 */
	UFUNCTION(BlueprintCallable)
	void SpawnLevelByIndex(const int Index);

	/** Destroy all elements in a spawn array and clear all timers */
	UFUNCTION(BlueprintCallable)
	void DeleteSpawnActors();

	/** Create Game over or Game win widget and call function DeleteSpawnActors() */
	UFUNCTION()
	void GameOverDelegateFunction();

protected:
	/** Override for get spawner and game state */
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AGameSpawner* Spawner;

	UPROPERTY()
	class AMobileGameStateBase* GameState;
};
