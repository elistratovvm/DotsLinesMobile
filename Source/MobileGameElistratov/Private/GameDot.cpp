// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDot.h"

AGameDot::AGameDot()
{
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Game Sphere"));
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereMesh->SetCollisionProfileName("BlockAll");
}
