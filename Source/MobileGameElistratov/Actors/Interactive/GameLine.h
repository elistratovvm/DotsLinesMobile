// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameLine.generated.h"

/** Class responsible for management of one line */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameLine : public AGameElement
{
	GENERATED_BODY()

public:
	/** Array of elements belonging to the line */
	UPROPERTY()
	TArray<AGameElement*> LineElements;

	/** Adds a score or reduces number of lives depending the line was successfully touched or not */
	virtual void Destroyed() override;

	/** Set bIsTouchBegin and bOnTheLine to true */
	void DotStartBeginTouch();

	/**
	 *	If bIsTouchBegin is true call function DestroyLine()
	 * @see DestroyLine()
	 */
	void DotStartEndTouch();

	/**	Set bOnTheLine to true */
	void EnterTouch();

	/**
	 *	Set bOnTheLine to false. If bIsTouchBegin is true, disabled collision for touched element
	 *	and set timer for 0.02 seconds per function DestroyLine() call.
	 * 
	 *	@param TouchedComponent			Element that was touched
	 * 
	 *	@see DestroyLine()
	 */
	void LeaveTouch(UPrimitiveComponent* TouchedComponent);
	
	/**
	 *	If bOnTheLine is false, clear DeathTimer and call function Destroy()
	 *	for all line elements and the line itself
	 */
	void DestroyLine();

private:
	/** If true, function DestroyLine() does not destroy line */
	bool bOnTheLine;

	/** Handle for checking out of the line */
	FTimerHandle DeathTimer;
};
