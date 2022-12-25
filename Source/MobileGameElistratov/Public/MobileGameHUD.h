// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MobileGameHUD.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EGameState
{
	MainMenu,
	PlayGame,
	GameOver,
	Settings,
};

UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* ModalWidget;

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentWidget(TEnumAsByte<EGameState> NewGameState);
	
protected:
	virtual void BeginPlay() override;
	
private:
	EGameState CurrentGameState;
};

