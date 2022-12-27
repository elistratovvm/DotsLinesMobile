// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GameSpawner.generated.h"

class AGameLine;
class AGameElement;

/** Type of element */
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

	/** Type of element */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGameElementType> GameElementType;

	/** Locations of elements */
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
	/** Default constructor for AGameSpawner */
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

	/** Destroy all spawned elements */
	void DestroyAllElements();

	/**
	 *	Remove deleted element from spawn array
	 *
	 *	@param GameActor		Removable element
	 */
	void RemoveOneElement(AGameElement* GameActor);
	
	/**
	 *	Spawn game elements from data table
	 *
	 *	@param FGameDataTable		Data table with game elements
	 *	@return QuantityElements	Quantity spawned elements
	 */
	float SpawnAndGetQuantityElements(const UDataTable* FGameTableDots);
	
protected:
	/** Override for check Blueprint settings */
	virtual void BeginPlay() override;

private:
	TArray<AGameElement*> GameElements;

	/**
	 *	Set timers for spawn elements
	 *
	 *	@param Data				Row data from fata table
	 */
	void SetSpawnTimer(FGameTableDots* Data);

	/**
	 *	Spawn start dot
	 *
	 *	@param Line				Line object to which dot belongs
	 *	@param Location			Location of dot
	 *	@param LifeTime			LifeTime of dot
	 */
	void SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime);

	/**
	 *	Spawn dot
	 *
	 *	@param Line				Line object to which dot belongs
	 *	@param Location			Location of dot
	 *	@param LifeTime			LifeTime of dot
	 */
	void SpawnDot(AGameLine* Line, FVector Location, float LifeTime);

	/**
	 *	Spawn spline mesh
	 *
	 *	@param Line				Line object to which spline mesh belongs
	 *	@param FirstLocation	Location of first dot
	 *	@param SecondLocation	Location of second dot
	 *	@param LifeTime			LifeTime of spline mesh
	 */
	void SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime);

	/**
	 *	Spawn sphere
	 *
	 *	@param Location			Location of sphere
	 *	@param LifeTime			LifeTime of sphere
	 */
	void SpawnSphere(FVector Location, float LifeTime);

	/**
	 *	Spawn line
	 *
	 *	@param Locations		Locations of elements
	 *	@param LifeTime			LifeTime of line
	 */
	void SpawnLine(TArray<FVector> Locations, float LifeTime);
};


