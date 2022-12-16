// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLine.h"

void AGameLine::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(0);
} 

void AGameLine::Destroyed()
{
	if (bIsTouched)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Line being touched!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Line dead from time!"));
	}
	Super::Destroyed();
}