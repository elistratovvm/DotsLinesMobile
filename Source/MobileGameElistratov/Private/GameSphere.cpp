// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSphere.h"

AGameSphere::AGameSphere()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");
}

void AGameSphere::TouchResponse()
{
	bIsTouched = true;
	Destroy();
}