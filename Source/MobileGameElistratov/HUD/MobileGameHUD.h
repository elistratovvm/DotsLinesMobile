// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MobileGameHUD.generated.h"

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

/** HUD for creating widget */
UCLASS()
class MOBILEGAMEELISTRATOV_API AMobileGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	/** Subclass of main menu widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	/** Subclass of play game widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> GameWidgetClass;

	/** Subclass of game over widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	/** Subclass of game win widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> GameWinWidgetClass;

	/** Subclass of settings widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	/** Subclass of level confirmation widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> LevelConfirmationWidgetClass;

	/** Subclass of pause widget. Settings on Blueprint. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	/** Current regular widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* CurrentWidget;

	/** Last called modal widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget* ModalWidget;

	/** Current selected level */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SelectedLevel;

	/**
	 *	Change game state and create the corresponding widget
	 *
	 *	@param NewGameState		New current game state
	 */
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
	
	void CreateRegularWidget(TSubclassOf<UUserWidget> WidgetClass);
	void CreateModalWidget(TSubclassOf<UUserWidget> WidgetClass);
	void FieldCheck() const;
};

