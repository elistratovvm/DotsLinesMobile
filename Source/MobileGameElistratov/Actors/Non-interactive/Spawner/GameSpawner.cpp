// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSpawner.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineMeshComponent.h"
#include "MobileGameElistratov/Actors/Interactive/Sphere/GameSphere.h"
#include "MobileGameElistratov/Actors/Interactive/Line/GameDot.h"
#include "MobileGameElistratov/Actors/Interactive/Line/GameDotStart.h"
#include "MobileGameElistratov/Actors/Interactive/Line/GameSplineMesh.h"
#include "MobileGameElistratov/Actors/Interactive/Line/GameLine.h"

AGameSpawner::AGameSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FieldCheck();
}

void AGameSpawner::DestroyAllElements()
{
	for (TIndexedContainerIterator Iterator = GameElements.CreateIterator(); Iterator; ++Iterator)
	{
		(*Iterator)->Destroy();
	}
	
	GameElements.Reset();
}

void AGameSpawner::RemoveOneElement(AGameElement* GameActor)
{
	if (GameElements.Contains(GameActor))
	{
		GameElements.Remove(GameActor);
	}
}

float AGameSpawner::SpawnAndGetQuantityElements(const UDataTable* GameTableDots)
{
	TArray<FGameTableDots*> DotsData;
	GameTableDots->GetAllRows(TEXT("Spawn dots"), DotsData);
	float QuantityElements = 0;
	
	for (FGameTableDots* Data : DotsData)
	{
		if (!Data->Locations.IsEmpty())
		{
			SetSpawnTimer(Data);
			QuantityElements++;
		}
	}
	
	return QuantityElements;
}

void AGameSpawner::SetSpawnTimer(FGameTableDots* Data)
{
	switch (Data->GameElementType)
	{
	case EGameElementType::DOTLN:
		{
			FTimerHandle LocalSpawnTimer;
			FTimerDelegate LocalTimerDel;

			if(Data->SpawnTime < 0.000001f)
			{
				Data->SpawnTime = 0.000001f;
			}
			LocalTimerDel.BindUObject(this, &AGameSpawner::SpawnLine, Data->Locations, Data->LifeTime);
			GetWorldTimerManager().SetTimer(LocalSpawnTimer, LocalTimerDel, Data->SpawnTime, false);
			break;
		}
	default:
		{
			FTimerHandle LocalSpawnTimer;
			FTimerDelegate LocalTimerDel;

			if(Data->SpawnTime < 0.000001f)
			{
				Data->SpawnTime = 0.000001f;
			}
			LocalTimerDel.BindUObject(this, &AGameSpawner::SpawnSphere, Data->Locations[0], Data->LifeTime);
			GetWorldTimerManager().SetTimer(LocalSpawnTimer, LocalTimerDel, Data->SpawnTime, false);
			break;
		}
	}
}

void AGameSpawner::SpawnSphere(FVector Location, float LifeTime)
{
	AGameSphere* Sphere = GetWorld()->SpawnActor<AGameSphere>(
		Sphere_Class,
		Location,
		FRotator());
	
	Sphere->SetLifeSpan(LifeTime);

	GameElements.Add(Sphere);
}

void AGameSpawner::SpawnLine(TArray<FVector> Locations, float LifeTime)
{
	const int32 SizeNum = Locations.Num();
	
	AGameLine* Line = GetWorld()->SpawnActor<AGameLine>();
	Line->SetLifeSpan(LifeTime);

	GameElements.Add(Line);
	
	SpawnDotStart(Line, Locations[0], LifeTime);

	SpawnSpline(
		Line,
		Locations[0],
		Locations[1],
		LifeTime);
			
	for (int32 i = 1; i < SizeNum - 1; i++)
	{
		SpawnDot(Line, Locations[i], LifeTime);

		SpawnSpline(
			Line,
			Locations[i],
			Locations[i + 1],
			LifeTime);
	}

	SpawnDotStart(Line, Locations[SizeNum - 1], LifeTime);
}

void AGameSpawner::SpawnDotStart(AGameLine* Line, FVector Location, float LifeTime)
{
	AGameDotStart* DotStart = GetWorld()->SpawnActor<AGameDotStart>(
		DotStart_Class,
		Location,
		FRotator());
	DotStart->SetLifeSpan(LifeTime);
	DotStart->LineObject = Line;
	
	Line->LineElements.Add(DotStart);
	GameElements.Add(DotStart);
}

void AGameSpawner::SpawnDot(AGameLine* Line, FVector Location, float LifeTime)
{
	AGameDot* Dot= GetWorld()->SpawnActor<AGameDot>(
			Dot_Class,
			Location,
			FRotator());
	Dot->SetLifeSpan(LifeTime);
	Dot->LineObject = Line;
	
	Line->LineElements.Add(Dot);
	GameElements.Add(Dot);
}

void AGameSpawner::SpawnSpline(AGameLine* Line, FVector FirstLocation, FVector SecondLocation, float LifeTime)
{
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FirstLocation,SecondLocation);
	const float EndPosX = sqrt(
		(SecondLocation.X - FirstLocation.X) * (SecondLocation.X - FirstLocation.X)
		+ (SecondLocation.Y - FirstLocation.Y) * (SecondLocation.Y - FirstLocation.Y));

	AGameSplineMesh* SplineMesh = GetWorld()->SpawnActor<AGameSplineMesh>(
		SplineMesh_Class,
		FirstLocation,
		Rotation);
	SplineMesh->SetLifeSpan(LifeTime);
	SplineMesh->Length = EndPosX;
	SplineMesh->LocationSecondDot = SecondLocation;
	SplineMesh->SplineMeshComponent->SetEndPosition(FVector(EndPosX, 0, 0));
	SplineMesh->SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
	SplineMesh->SplineMeshComponent->SetStartScale(FVector2D(0.8));
	SplineMesh->SplineMeshComponent->SetEndScale(FVector2D(0.8));
	SplineMesh->LineObject = Line;
	
	Line->LineElements.Add(SplineMesh);
	GameElements.Add(SplineMesh);
}

void AGameSpawner::FieldCheck() const
{
	if (!Sphere_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Sphere class. Did you make assigment on Blueprint?"));
	}
	if (!Dot_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Dot class. Did you make assigment on Blueprint?"));
	}
	if (!DotStart_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Dot Start class. Did you make assigment on Blueprint?"));
	}
	if (!SplineMesh_Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the SplineMesh class. Did you make assigment on Blueprint?"));
	}
}
