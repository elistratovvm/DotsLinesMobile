// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MobileGameStateBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);

UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	/** Current score per level */
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentScore;

	/** Maximum value of health point */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Settings")
	int32 MaxHealthPoint;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealthPoint;

	/** Quantity element for game continue. If equal zero, the game will be over. */
	int32 QuantityElementForGame;

	/** Dynamic delegate for game over */
	FGameOver GameOver;
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentScore();
	
	UFUNCTION(BlueprintCallable)
	void ResetCurrentScore();
	
	UFUNCTION(BlueprintCallable)
	void ResetCurrentHealth();
	
	void AddCurrentScore(float AddedScore);
	void DecreaseHealthPoint();
	void DecreaseQuantityElement();
	void GameOverFunction() const;
};
