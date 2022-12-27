// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDot.h"
#include "GameDotStart.generated.h"

/** Part of the line which begins and ends the interaction of the line */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameDotStart : public AGameDot
{
	GENERATED_BODY()

public:
	/** Default constructor for AGameDotStart */
	AGameDotStart();

	/**
	 *	Event for start line interaction
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		UPrimitiveComponent of dot
	 */
	UFUNCTION()
	void InputTouchBeginResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/**
	 *	Event for end line interaction
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		UPrimitiveComponent of dot
	 */
	UFUNCTION()
	void InputTouchEndResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
protected:
	/** Call EnterTouch() of LineObject */
	virtual void EnterResponse() override;

	/** Call LeaveTouch() of LineObject
	 *
	 *	@param TouchedComponent		UPrimitiveComponent of dot
	 */
	virtual void LeaveResponse(UPrimitiveComponent* TouchedComponent) override;
};
