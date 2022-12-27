// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobileGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMobileGamePlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACameraActor* MainCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsGameVibrateOn = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsMenuVibrateOn = true;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//TODO::Check if this functions are needed
	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
};
