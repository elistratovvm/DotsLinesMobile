// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameSpawner.generated.h"

class AGameLine;
class AGameElement;
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSphere> Sphere_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDot> Dot_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDotStart> DotStart_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSplineMesh> SplineMesh_Class;
	
	UFUNCTION(BlueprintCallable)
	TArray<AGameElement*> GetSpawnElements();
	UFUNCTION(BlueprintCallable)
	void ReadAndSpawn(const UDataTable* FGameTableDots);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<AGameElement*> GameElements;

	void CreateSpawnTimer(FGameTableDots* Data, FName FunctionName);
	UFUNCTION()
	void SpawnSphere(FVector SpawnLocation, float LifeTime);
	UFUNCTION()
	void SpawnLine(TArray<FVector> Locations, float LifeTime);
	void SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnDot(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime);
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
