// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameLine.generated.h"

/** Maybe this class will be removed
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameLine : public AGameElement
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void Destroyed() override;
};
