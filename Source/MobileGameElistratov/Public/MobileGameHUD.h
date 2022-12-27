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
	GameWin,
	Settings,
	LevelConfirmation,
	Pause
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
	TSubclassOf<UUserWidget> GameWinWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> LevelConfirmationWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* ModalWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SelectedLevel;

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentWidget(TEnumAsByte<EGameState> NewGameState);

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameState(TEnumAsByte<EGameState> NewGameState);

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState();
	
protected:
	virtual void BeginPlay() override;
	
private:
	EGameState CurrentGameState;

	void FieldCheck() const;
	void CreateRegularWidget(TSubclassOf<UUserWidget> WidgetClass);
	void CreateModalWidget(TSubclassOf<UUserWidget> WidgetClass);
};

