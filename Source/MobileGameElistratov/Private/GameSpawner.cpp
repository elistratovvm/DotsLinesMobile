// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSpawner.h"
#include "GameDot.h"
#include "GameDotStart.h"
#include "GameLine.h"
#include "GameSphere.h"
#include "GameSplineMesh.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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

TArray<AGameElement*> AGameSpawner::GetSpawnElements()
{
	return GameElements;
}

void AGameSpawner::ReadAndSpawn(const UDataTable* GameTableDots)
{
	TArray<FGameTableDots*> DotsData;
	GameTableDots->GetAllRows(TEXT("Spawn dots"), DotsData);
	
	for (FGameTableDots* Data : DotsData)
	{
		switch (Data->GameElementType)
		{
		case EGameElementType::SPHER:
			{
				CreateSpawnTimer(Data, FName("SpawnSphere"));
				break;
			}
		case EGameElementType::DOTLN:
			{
				CreateSpawnTimer(Data, FName("SpawnLine"));
				break;
			}
		}
	}
}

void AGameSpawner::CreateSpawnTimer(FGameTableDots* Data, FName FunctionName)
{
	FTimerHandle LocalSpawnTimer;
	FTimerDelegate LocalTimerDel;

	if (Data->SpawnTime < 0.0001f)
	{
		Data->SpawnTime = 0.0001f;
	}
	
	LocalTimerDel.BindUFunction(this, FunctionName, Data->Locations, Data->LifeTime);
	GetWorldTimerManager().SetTimer(LocalSpawnTimer, LocalTimerDel, Data->SpawnTime, false);
}

void AGameSpawner::SpawnSphere(FVector Location, float LifeTime)
{
	AGameSphere* Sphere = GetWorld()->SpawnActor<AGameSphere>(
		Sphere_Class,
		Location,
		FRotator());
	
	Sphere->PostSetLifeSpan(LifeTime);

	GameElements.Add(Sphere);
}

void AGameSpawner::SpawnLine(TArray<FVector> Locations, float LifeTime)
{
	const int32 SizeNum = Locations.Num();
	
	AGameLine* Line = GetWorld()->SpawnActor<AGameLine>();
	Line->PostSetLifeSpan(LifeTime);

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
	
	DotStart->PostSetLifeSpan(LifeTime);
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
	Dot->PostSetLifeSpan(LifeTime);
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
	SplineMesh->PostSetLifeSpan(LifeTime);
	SplineMesh->Length = EndPosX;
	SplineMesh->SplineMeshComponent->SetEndPosition(FVector(EndPosX, 0, 0));
	SplineMesh->SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
	SplineMesh->SplineMeshComponent->SetStartScale(FVector2D(0.8));
	SplineMesh->SplineMeshComponent->SetEndScale(FVector2D(0.8));
	SplineMesh->LineManager = Line;
	
	Line->Splines.Add(SplineMesh);
	GameElements.Add(SplineMesh);
}


