// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MobileSaveGame.generated.h"

/** Save class */
UCLASS()
class MOBILEGAMEELISTRATOV_API UMobileSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMobileSaveGame();
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Record;

};
