// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameSplineMesh.generated.h"

/**
 * 
 */

class AMobileGamePlayerController;
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSplineMesh : public AGameElement
{
	GENERATED_BODY()

public:
	AGameSplineMesh();

	
	float DistanceToFirstDot;
	float DistanceToSecondDot;
	float Length;
	
	FVector ActorSecondDot;
	FVector VectorLocation;
	FVector VectorDirection;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineMeshComponent* SplineMeshComponent;
	
	UPROPERTY()
	class AGameLine* LineManager;
	
	UPROPERTY()
	AMobileGamePlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly)
	float LineProgress = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bIsReverse = false;

	
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

	
	UFUNCTION()
	void InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
	UFUNCTION()
	void InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

protected:
	virtual void BeginPlay() override;
	
private:
	float CurrentScore = 0.f;
	int32 NumberOfTicks = 0;

	
	float GetDistance(FVector FirstDot, FVector SecondDot) const;
};
