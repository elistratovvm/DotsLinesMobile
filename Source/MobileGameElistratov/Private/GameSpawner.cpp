// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSpawner.h"

#include "GameDot.h"
#include "GameDotStart.h"
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

// Called when the game starts or when spawned
void AGameSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameSpawner::ReadAndSpawn(const UDataTable* GameTableDots)
{
	// The C++ API gives you more convenient tools for working with tables.
	// There is no need to look up table rows by name, you can get the whole array at once.
	// I left an example of this as a comment below.
	TArray<FName> RowNames = GameTableDots->GetRowNames();
	for (const FName RowName : RowNames)
	{
		if (FGameTableDots* GameElement = GameTableDots->FindRow<FGameTableDots>(
				RowName,
				"Reading Level Row");
			GameElement->GameElementType == SPHER) // Too long condition
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
				SpawnLine(GameElement, SizeNum); // Why we need pass SizeNum and GameElement if SizeNum produced from GameElement?
			}
		}
	}
	
	/*TArray<FGameTableDots*> DotsData;
	GameTableDots->GetAllRows(TEXT("Spawn dots"), DotsData);
	for (const FGameTableDots* Data : DotsData)
	{
		switch (Data->GameElementType)
		{
		case EGameElementType::DOTLN:
			{
				SpawnSphere(Data->Locations[0], Data->LifeTime);
				break;
			}
		case EGameElementType::SPHER:
			{
				SpawnLine(Data, Data->Locations.Num());
				break;
			}
		}
	}*/
}

void AGameSpawner::SpawnSphere(FVector SpawnLocation, float LifeTime) const
{
	AGameSphere* Sphere = GetWorld()->SpawnActor<AGameSphere>(
		GameElementSphere,
		SpawnLocation,
		FRotator());
	Sphere->LifeTime = LifeTime;
}

void AGameSpawner::SpawnLine(/*maybe const*/ FGameTableDots* GameElement, float SizeNum) const
{
	AGameDotStart* DotStart = GetWorld()->SpawnActor<AGameDotStart>(
		GameElementDotStart,
		GameElement->Locations[0],
		FRotator());
	DotStart->LifeTime = GameElement->LifeTime;

	SpawnSpline(
		GameElement->Locations[0],
		GameElement->Locations[1],
		GameElement->LifeTime);

	for (int32 i = 1; i < SizeNum - 1; i++)
	{
		AGameDot* Dot = GetWorld()->SpawnActor<AGameDot>(
			GameElementDot,
			GameElement->Locations[i],
			FRotator());
		Dot->LifeTime = GameElement->LifeTime;

		SpawnSpline(
			GameElement->Locations[i],
			GameElement->Locations[i + 1],
			GameElement->LifeTime);
	}

	AGameDotStart* DotEnd = GetWorld()->SpawnActor<AGameDotStart>(
		GameElementDotStart,
		GameElement->Locations[SizeNum - 1],
		FRotator());
	DotEnd->LifeTime = GameElement->LifeTime;
}

void AGameSpawner::SpawnSpline(FVector FirstLocation, FVector SecondLocation, float LifeTime) const
{
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FirstLocation, SecondLocation);
	const float EndPosX = sqrt(
		(SecondLocation.X - FirstLocation.X) * (SecondLocation.X - FirstLocation.X)
		+ (SecondLocation.Y - FirstLocation.Y) * (SecondLocation.Y - FirstLocation.Y)
		+ (SecondLocation.Z - FirstLocation.Z) * (SecondLocation.Z - FirstLocation.Z));

	AGameSplineMesh* SplineMesh = GetWorld()->SpawnActor<AGameSplineMesh>(
		GameElementSplineMesh,
		FirstLocation,
		Rotation);

	SplineMesh->LifeTime = LifeTime;
	SplineMesh->Length = EndPosX;
	SplineMesh->SplineMeshComponent->SetEndPosition(FVector(EndPosX, 0, 0));
	SplineMesh->SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
	SplineMesh->SplineMeshComponent->SetStartScale(FVector2D(0.8));
	SplineMesh->SplineMeshComponent->SetEndScale(FVector2D(0.8));
}
