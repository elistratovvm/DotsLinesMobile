// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameSplineMesh.generated.h"

/**
 * 
 */

UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSplineMesh : public AGameElement
{
	GENERATED_BODY()

	
public:
	AGameSplineMesh();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineMeshComponent* SplineMeshComponent;

	float Length;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
