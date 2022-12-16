// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameSpawner.generated.h"

struct FGameTableDots;
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSpawner();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ReadAndSpawn(const UDataTable* FGameTableDots);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSphere> GameElementSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDot> GameElementDot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDotStart> GameElementDotStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSplineMesh> GameElementSplineMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SpawnSpline(FVector FirstLocation, FVector SecondLocation, float LifeTime) const;
	void SpawnSphere(FVector SpawnLocation, float LifeTime) const;
	void SpawnLine(FGameTableDots* GameElement, float SizeNum) const;
};

UENUM(BlueprintType)
enum EGameElementType
{
	SPHER,
	DOTLN,
};

USTRUCT(BlueprintType)
struct FGameTableDots : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGameElementType> GameElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Locations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime;
};
