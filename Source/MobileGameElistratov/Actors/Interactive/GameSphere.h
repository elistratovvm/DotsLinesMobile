// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameSphere.generated.h"

/** Game sphere class */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSphere : public AGameElement
{
	GENERATED_BODY()
public:
	/** Default constructor for AGameSphere */
	AGameSphere();

	/** Sphere Mesh */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	/** Adds a score or reduces number of lives depending sphere was successfully touched or not */
	virtual void Destroyed() override;

	/** Calculates score for interaction with sphere when touch begin */
	UFUNCTION()
	void InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/** Destroy sphere when touch ends */
	UFUNCTION()
	void InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
private:
	/** Score for interaction with sphere */
	float CurrentScore;
};
