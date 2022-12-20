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
	TArray<class AGameDotStart*> DotsStart;
	TArray<class AGameDot*> Dots;
	TArray<class AGameSplineMesh*> Splines;
	
	void PrintText() const;
	virtual void Destroyed() override;
	void DotStartBeginTouch();
	void DotStartEndTouch();
	void DotEnterTouch();
	void DotLeaveTouch(UPrimitiveComponent* TouchedComponent);
	void SplineMeshLeaveTouch(UPrimitiveComponent* TouchedComponent);
	void EnterTouch();
	void LeaveTouch(UPrimitiveComponent* TouchedComponent);
	void DestroyLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bOnTheLine;
	bool bOnDot;
	bool bIsLineStarted;
	FTimerHandle DeathTimer;
};
