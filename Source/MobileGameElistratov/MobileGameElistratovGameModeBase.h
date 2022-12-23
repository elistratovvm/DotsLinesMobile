// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobileGameElistratovGameModeBase.generated.h"

/**
 * 
 */
class AGameManager;
 
UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameElistratovGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMobileGameElistratovGameModeBase();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGameManager> GameManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameManager* GameManager_BP;
    
protected:
   	virtual void BeginPlay() override;
};
