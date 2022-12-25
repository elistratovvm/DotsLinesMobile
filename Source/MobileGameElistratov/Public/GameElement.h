// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameElement.generated.h"

/** Parent class of all game elements */
UCLASS()
class MOBILEGAMEELISTRATOV_API AGameElement : public AActor
{
	GENERATED_BODY()
public:
	AGameElement();

	/** Element touch begin by something */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchBegin = false;

	/** Element touch end by something */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bIsTouchEnd = false;

	/** Maximum score for interacting with element */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float MaxScore;

	/** Remove element from array of spawned elements */
	virtual void BeginDestroy() override;
};
