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

	float Length;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineMeshComponent* SplineMeshComponent;

	UPROPERTY()
	class AGameLine* LineManager;
	
	UFUNCTION()
	void InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
