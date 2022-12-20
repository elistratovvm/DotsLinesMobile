// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobileGameModeBase.generated.h"

/**
 * 
 */
class AGameManager;

UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameManager* GameManager_BP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGameManager> GameManager;

protected:
	virtual void BeginPlay() override;
};
