// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileGameHUD.h"

#include "Blueprint/UserWidget.h"

void AMobileGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	FieldCheck();

	CurrentGameState = EGameState::MainMenu;
	
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
	CurrentWidget->AddToViewport(0);	
}


void AMobileGameHUD::ChangeCurrentWidget(TEnumAsByte<EGameState> NewGameState)
{
	CurrentGameState = NewGameState;
	
	switch(CurrentGameState)
	{
	case EGameState::PlayGame:
		{
			CreateRegularWidget(GameWidgetClass);
			break;
		}
	case EGameState::Settings:
		{
			CreateRegularWidget(SettingsWidgetClass);
			break;
		}
	case EGameState::GameOver:
		{
			CreateModalWidget(GameOverWidgetClass);
			break;
		}
	case EGameState::GameWin:
		{
			CreateModalWidget(GameWinWidgetClass);
			break;
		}
	case EGameState::LevelConfirmation:
		{
			CreateModalWidget(LevelConfirmationWidgetClass);
			break;
		}
	case EGameState::Pause:
		{
			CreateModalWidget(PauseWidgetClass);
			break;
		}
	default:
		{
			CreateRegularWidget(MainMenuWidgetClass);
			break;
		}
	}
}

void AMobileGameHUD::SetCurrentGameState(TEnumAsByte<EGameState> NewGameState)
{
	CurrentGameState = NewGameState;
}

EGameState AMobileGameHUD::GetCurrentGameState()
{
	return CurrentGameState;
}

void AMobileGameHUD::CreateRegularWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
	CurrentWidget->AddToViewport(0);
}

void AMobileGameHUD::CreateModalWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	ModalWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
	ModalWidget->AddToViewport(0);
}

void AMobileGameHUD::FieldCheck() const
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not find the Main Menu Widget class. Did you make assigment on Blueprint?"));
	}
	if (!GameWidgetClass)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not find the Game Widget class. Did you make assigment on Blueprint?"));
	}
	if (!GameOverWidgetClass)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not find the Game Over Widget class. Did you make assigment on Blueprint?"));
	}
	if (!GameWinWidgetClass)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not find the Game Win Widget class. Did you make assigment on Blueprint?"));
	}
	if (!SettingsWidgetClass)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not find the Settings Widget class. Did you make assigment on Blueprint?"));
	}
	if (!LevelConfirmationWidgetClass)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not find the Level Confirmation Widget class. Did you make assigment on Blueprint?"));
	}
	if (!PauseWidgetClass)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Could not find the Pause Widget class. Did you make assigment on Blueprint?"));
	}
}