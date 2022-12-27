// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameDot.generated.h"

/** Part of the line along which line is drawn */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameDot : public AGameElement
{
	GENERATED_BODY()
public:
	/** Default constructor for AGameDot */
	AGameDot();

	/** Sphere Mesh. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	/** Line object to which dot belongs */
	UPROPERTY()
	class AGameLine* LineObject;

	/** Override for adds a score if line and dot were successfully touched */
	virtual void Destroyed() override;

	/**
	 *	Event for call EnterResponse()
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		UPrimitiveComponent of dot
	 *	
	 *	@see EnterResponse()
	 */
	UFUNCTION()
	void InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
	/**
	 *	Event for call LeaveResponse()
	 *
	 *	@param FingerIndex			The index of finger that touched the dot
	 *	@param TouchedComponent		UPrimitiveComponent of dot
	 *	
	 *	@see LeaveResponse()
	 */
	UFUNCTION()
	void InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

protected:
	/** If line successfully touched, call EnterTouch() of LineObject */
	virtual void EnterResponse();
	
	/** If line and dot successfully touched, call LeaveTouch() of LineObject
	 *
	 *	@param TouchedComponent			UPrimitiveComponent of dot
	 */
	virtual void LeaveResponse(UPrimitiveComponent* TouchedComponent);
};
