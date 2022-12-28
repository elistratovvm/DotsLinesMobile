// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobileGamePlayerController.generated.h"

/** Player Controller class */
UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMobileGamePlayerController();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACameraActor* MainCamera;

	/** If true, when interacting with game elements device will vibrate */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsGameVibrateOn = true;

	/** If true, when interacting with menu elements device will vibrate */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsMenuVibrateOn = true;
	
protected:
	/** Override for set Main Camera */
	virtual void BeginPlay() override;
};
