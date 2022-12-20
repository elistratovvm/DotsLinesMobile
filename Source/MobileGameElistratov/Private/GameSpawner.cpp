// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSpawner.h"

#include "GameDot.h"
#include "GameDotStart.h"
#include "GameLine.h"
#include "GameSphere.h"
#include "GameSplineMesh.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGameSpawner::AGameSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<AGameElement*> AGameSpawner::GetSpawnElements()
{
	return GameElements;
}

// Called when the game starts or when spawned
void AGameSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Sphere_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Sphere class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!Dot_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Dot class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!DotStart_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Dot Start class. Did you make assigment on Blueprint?"));
		return;
	}
	if (!SplineMesh_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the SplineMesh class. Did you make assigment on Blueprint?"));
		return;
	}
}

void AGameSpawner::ReadAndSpawn(const UDataTable* GameTableDots)
{
	TArray<FName> RowNames = GameTableDots->GetRowNames();

	for (const FName RowName : RowNames)
	{
		if (FGameTableDots* GameElement = GameTableDots->FindRow<FGameTableDots>(
				RowName,
				"Reading Level Row");
			GameElement->GameElementType == SPHER)
		{
			SpawnSphere(GameElement->Locations[0], GameElement->LifeTime);
		}
		else
		{
			const int32 SizeNum = GameElement->Locations.Num();

			if (SizeNum == 1)
			{
				SpawnSphere(GameElement->Locations[0], GameElement->LifeTime);
			}
			else
			{
				SpawnLine(GameElement, SizeNum);
			}
		}
	}
}

void AGameSpawner::SpawnSphere(FVector SpawnLocation, float LifeTime)
{
	AGameSphere* Sphere = GetWorld()->SpawnActor<AGameSphere>(
		Sphere_Class,
		SpawnLocation,
		FRotator());
	Sphere->LifeTime = LifeTime;

	GameElements.Add(Sphere);
}

void AGameSpawner::SpawnLine(FGameTableDots* GameElement, float SizeNum)
{
	AGameLine* Line = GetWorld()->SpawnActor<AGameLine>();
	Line->LifeTime = GameElement->LifeTime;

	GameElements.Add(Line);
	
	SpawnDotStart(Line, GameElement->Locations[0], GameElement->LifeTime);

	SpawnSpline(
		Line,
		GameElement->Locations[0],
		GameElement->Locations[1],
		GameElement->LifeTime);
			
	for (int32 i = 1; i < SizeNum - 1; i++)
	{
		SpawnDot(Line, GameElement->Locations[i], GameElement->LifeTime);

		SpawnSpline(
			Line,
			GameElement->Locations[i],
			GameElement->Locations[i + 1],
			GameElement->LifeTime);
	}

	SpawnDotStart(Line, GameElement->Locations[SizeNum - 1], GameElement->LifeTime);

	//Debug method, delete after development will be completed
	//------------------------------------------------------------------------------------------------------------------
	Line->PrintText();
	//------------------------------------------------------------------------------------------------------------------
}

void AGameSpawner::SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime)
{
	AGameDotStart* DotStart = GetWorld()->SpawnActor<AGameDotStart>(
		DotStart_Class,
		Location,
		FRotator());
	DotStart->LifeTime = LifeTime;
	DotStart->LineManager = Line;
	
	Line->DotsStart.Add(DotStart);
	GameElements.Add(DotStart);
}

void AGameSpawner::SpawnDot(AGameLine* Line, FVector Location, float LifeTime)
{
	AGameDot* Dot= GetWorld()->SpawnActor<AGameDot>(
			Dot_Class,
			Location,
			FRotator());
	Dot->LifeTime = LifeTime;
	Dot->LineManager = Line;
	
	Line->Dots.Add(Dot);
	GameElements.Add(Dot);
}

void AGameSpawner::SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime)
{
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FirstLocation,SecondLocation);
	const float EndPosX = sqrt(
		(SecondLocation.X - FirstLocation.X) * (SecondLocation.X - FirstLocation.X)
		+ (SecondLocation.Y - FirstLocation.Y) * (SecondLocation.Y - FirstLocation.Y)
		+ (SecondLocation.Z - FirstLocation.Z) * (SecondLocation.Z - FirstLocation.Z));

	AGameSplineMesh* SplineMesh = GetWorld()->SpawnActor<AGameSplineMesh>(
		SplineMesh_Class,
		FirstLocation,
		Rotation);
	SplineMesh->LifeTime = LifeTime;
	SplineMesh->Length = EndPosX;
	SplineMesh->SplineMeshComponent->SetEndPosition(FVector(EndPosX, 0, 0));
	SplineMesh->SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
	SplineMesh->SplineMeshComponent->SetStartScale(FVector2D(0.8));
	SplineMesh->SplineMeshComponent->SetEndScale(FVector2D(0.8));
	SplineMesh->LineManager = Line;
	
	Line->Splines.Add(SplineMesh);
	GameElements.Add(SplineMesh);
}

