// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameDot.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameDot : public AGameElement
{
	GENERATED_BODY()
public:
	AGameDot();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SphereMesh;
};
