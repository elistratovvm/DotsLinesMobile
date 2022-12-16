// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSplineMesh.h"
#include "Components/SplineMeshComponent.h"

AGameSplineMesh::AGameSplineMesh()
{
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Game Spline Mesh Component"));
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SplineMeshComponent->SetCollisionProfileName("BlockAll");
}

// Called when the game starts or when spawned
void AGameSplineMesh::BeginPlay()
{
	Super::BeginPlay();
}
