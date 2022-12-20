// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class UDataTable;
class AGameSpawner;

UCLASS()
class MOBILEGAMEELISTRATOV_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> Overlay_Class;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AGameSpawner> Spawner_Class;
	UPROPERTY()
	UUserWidget* Overlay;

	UFUNCTION(BlueprintCallable)
	void SpawnLevel(const UDataTable* FGameTableDots) const;
	UFUNCTION(BlueprintCallable)
	void DeleteSpawnActors();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AGameSpawner* Spawner;
};
