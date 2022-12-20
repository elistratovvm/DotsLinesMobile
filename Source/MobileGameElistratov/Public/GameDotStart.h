// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDot.h"
#include "GameDotStart.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameDotStart : public AGameDot
{
	GENERATED_BODY()

public:
	AGameDotStart();
	
	UFUNCTION()
	void InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
	virtual void EnterResponse() override;
	virtual void LeaveResponse(UPrimitiveComponent* TouchedComponent) override;
};
