// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameSphere.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSphere : public AGameElement
{
	GENERATED_BODY()
public:
	AGameSphere();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
};
