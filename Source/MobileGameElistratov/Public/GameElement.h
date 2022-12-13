// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameElement.generated.h"

UCLASS()
class MOBILEGAMEELISTRATOV_API AGameElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameElement();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouched;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float SpawnTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float LifeTime = 5.f;*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	
	void TouchResponse();
};
