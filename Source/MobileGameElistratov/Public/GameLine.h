// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameLine.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameLine : public AGameElement
{
	GENERATED_BODY()

public:
	//TODO:: Check possibility of using 1 array
	TArray<class AGameDotStart*> DotsStart;
	TArray<class AGameDot*> Dots;
	TArray<class AGameSplineMesh*> Splines;

	
	virtual void Destroyed() override;
	
	void DotStartBeginTouch();
	void DotStartEndTouch();
	//TODO:: Refactor unused Dot class logic
	void DotEnterTouch();
	void DotLeaveTouch(UPrimitiveComponent* TouchedComponent);
	//TODO:: Refactor unused SplineMesh class logic
	void SplineMeshLeaveTouch(UPrimitiveComponent* TouchedComponent);
	void EnterTouch();
	void LeaveTouch(UPrimitiveComponent* TouchedComponent);
	void DestroyLine();

#if WITH_EDITOR
	void PrintText() const;
#endif

protected:
	virtual void BeginPlay() override;

private:
	bool bOnTheLine;
	//TODO:: Refactor unused Dot class logic
	bool bOnDot;
	FTimerHandle DeathTimer;
};
