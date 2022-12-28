// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobileGameElistratovGameModeBase.generated.h"

class AGameManager;

/** Game mode class */
UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameElistratovGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMobileGameElistratovGameModeBase();

	/** Subclass of game manager. Settings on Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGameManager> GameManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameManager* GameManager_BP;
    
protected:
   	virtual void BeginPlay() override;
};
