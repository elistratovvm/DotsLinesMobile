// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameElement.generated.h"

/** Parent class of all custom game elements */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameElement : public AActor
{
	GENERATED_BODY()
public:
	/** Default constructor for AGameElement */
	AGameElement();

	/** If true, function requiring touch can be fired */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchBegin = false;

	/** If true, score for elements can be awarded */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchEnd = false;

	/** Maximum score for interacting with element */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float MaxScore;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feedback")
	UForceFeedbackEffect* MobileForceFeedbackEffect;

	/** Remove element from array of spawned elements */
	virtual void BeginDestroy() override;
};