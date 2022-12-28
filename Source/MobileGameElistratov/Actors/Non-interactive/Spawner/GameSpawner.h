// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameSpawner.generated.h"

class AGameLine;
class AGameElement;

UENUM(BlueprintType)
enum EGameElementType
{
	SPHER,
	DOTLN,
};

/** Structure with data about level elements */
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

/** Element spawner */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AGameSpawner();

	/** Subclass of sphere. Settings on Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSphere> Sphere_Class;

	/** Subclass of dot. Settings on Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDot> Dot_Class;

	/** Subclass of start dot. Settings on Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameDotStart> DotStart_Class;

	/** Subclass of spline mesh. Settings on Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGameSplineMesh> SplineMesh_Class;
	
	void DestroyAllElements();
	
	void RemoveOneElement(AGameElement* GameActor);
	
	/**
	 *	Spawn game elements from data table
	 *
	 *	@param FGameDataTable		Data table with game elements
	 *	
	 *	@return QuantityElements	Quantity spawned elements
	 */
	float SpawnAndGetQuantityElements(const UDataTable* FGameDataTable);
	
protected:
	/** Override for check Blueprint settings */
	virtual void BeginPlay() override;

private:
	TArray<AGameElement*> GameElements;
	
	void SetSpawnTimer(FGameTableDots* Data);
	
	void SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnDot(AGameLine* Line, FVector Location, float LifeTime);
	void SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime);
	void SpawnSphere(FVector Location, float LifeTime);
	void SpawnLine(TArray<FVector> Locations, float LifeTime);
	void FieldCheck() const;
};


