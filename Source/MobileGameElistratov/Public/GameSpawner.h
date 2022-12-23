// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameSpawner.generated.h"

class AGameLine;
class AGameElement;
struct FGameTableDots;
enum EGameElementType;

UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameSpawner();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSphere> Sphere_Class;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDot> Dot_Class;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDotStart> DotStart_Class;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSplineMesh> SplineMesh_Class;

	
	void DestroyAllElements();
	void RemoveOneElement(AGameElement* GameActor);
	//TODO:: Make two function from this
	float SpawnAndGetLevelTime(const UDataTable* FGameTableDots);
	
protected:
	virtual void BeginPlay() override;

private:
	TArray<AGameElement*> GameElements;

	
	void SetSpawnTimer(FGameTableDots* Data, float* MaxLifeTime);
	void SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnDot(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime);

	
	UFUNCTION()
	void SpawnSphere(FVector Location, float LifeTime);
	
	UFUNCTION()
	void SpawnLine(TArray<FVector> Locations, float LifeTime);
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
