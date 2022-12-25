// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElement.h"
#include "GameDot.generated.h"

/** Part of line along which line is drawn */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameDot : public AGameElement
{
	GENERATED_BODY()
public:
	AGameDot();

	/** Sphere Mesh */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	/** Line object to which dot belongs */
	UPROPERTY()
	class AGameLine* LineManager;

	/** Adds a score if line and dot were successfully touched */
	virtual void Destroyed() override;

	/** Call EnterResponse() */
	UFUNCTION()
	void InputTouchEnterResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
	/** Call LeaveResponse() */
	UFUNCTION()
	void InputTouchLeaveResponse(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

protected:
	
	virtual void EnterResponse();
	virtual void LeaveResponse(UPrimitiveComponent* TouchedComponent);
};
