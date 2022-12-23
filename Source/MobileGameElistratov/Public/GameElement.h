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
	AGameElement();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchBegin;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchEnd;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float MaxScore;

	
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;
	virtual void SetLifeTime(float LifeTime);
};
