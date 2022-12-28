// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameElement.h"
#include "GameSplineMesh.generated.h"

/** Part of the line that connects the dots */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameSplineMesh : public AGameElement
{
	GENERATED_BODY()

public:
	/** Default constructor for AGameSplineMesh */
	AGameSplineMesh();

	/** Length of spline mesh */
	float Length;

	/** Location of second dot of spline mesh */
	FVector LocationSecondDot;
	
	/** Spline mesh component. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineMeshComponent* SplineMeshComponent;

	/** Line object to which spline mesh belongs */
	UPROPERTY()
	class AGameLine* LineObject;

	/** Line progress, from 0 to 1 */
	UPROPERTY(BlueprintReadOnly)
	float LineProgress = 0.f;

	/** If true, the spline mesh moves in the opposite direction */
	UPROPERTY(BlueprintReadOnly)
	bool bIsReverse = false;

	/** Override for calculate score for the line */
	virtual void Tick(float DeltaSeconds) override;

	/** Override for adds a score if line and spline mesh were successfully touched */
	virtual void Destroyed() override;

	/**
	 *	Event for assign a value bIsReverse  and call function EnterTouch() of LineObject
	 *	if line were successfully touched
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		Element that was touched (In this case, the dot)
	 */
	UFUNCTION()
	void InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/**
	 *	Event for complete line progress and  call function LeaveTouch() of LineObject
	 *	if line and spline mesh were successfully touched
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		Element that was touched (In this case, the dot)
	 */
	UFUNCTION()
	void InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

protected:
	/** Override for get Player Controller */
	virtual void BeginPlay() override;
	
private:
	/** Distance to first dot of spline mesh */
	float DistanceToFirstDot;

	/** Distance to second dot of spline mesh */
	float DistanceToSecondDot;

	/** Percentage of core from maximum score, from 0 to 1 */
	float ScorePercent = 0.f;
	
	int32 QuantityOfTicks = 0;

	/** Location Vector for method DeprojectMousePositionToWorld() of PlayerController */
	FVector VectorLocation;
	
	/** Direction Vector for method DeprojectMousePositionToWorld() of PlayerController */
	FVector VectorDirection;

	UPROPERTY()
	class AMobileGamePlayerController* PlayerController;

	/**
	 * Get distance in x and y between FirstDot and SecondDot
	 *
	 * @param FirstDot		FVector with location of first dot
	 * @param SecondDot		FVector with location of second dot
	 */
	float GetDistance(FVector FirstDot, FVector SecondDot) const;
};
