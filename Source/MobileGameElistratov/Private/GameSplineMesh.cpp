// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSplineMesh.h"

#include "GameLine.h"
#include "Components/SplineMeshComponent.h"

AGameSplineMesh::AGameSplineMesh()
{
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Game Spline Mesh Component"));
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SplineMeshComponent->SetCollisionProfileName("BlockAll");
	
	SplineMeshComponent->OnInputTouchEnter.AddDynamic(this, &AGameSplineMesh::InputTouchEnterResponse);
	SplineMeshComponent->OnInputTouchLeave.AddDynamic(this, &AGameSplineMesh::InputTouchLeaveResponse);
}

// Called when the game starts or when spawned
void AGameSplineMesh::BeginPlay()
{
	Super::BeginPlay();
}

void AGameSplineMesh::InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Spline Touch Enter!"));
	LineManager->EnterTouch();
}

void AGameSplineMesh::InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spline Touch Leave!"));
	LineManager->LeaveTouch(TouchedComponent);
	//SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
