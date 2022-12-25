// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileGameHUD.h"

#include "Blueprint/UserWidget.h"

void AMobileGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Main Menu class. Did you make assigment on Blueprint?"));
	}
	if (!GameWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Game Widget class. Did you make assigment on Blueprint?"));
	}
	if (!GameOverWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Game Over class. Did you make assigment on Blueprint?"));
	}
	if (!SettingsWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find the Settings Widget class. Did you make assigment on Blueprint?"));
	}

	CurrentGameState = EGameState::MainMenu;
	
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
	CurrentWidget->AddToViewport(0);	
}

void AMobileGameHUD::ChangeCurrentWidget(TEnumAsByte<EGameState> NewGameState)
{
	CurrentGameState = NewGameState;
	
	switch(CurrentGameState)
	{
	case EGameState::MainMenu:
		{
			CurrentWidget->RemoveFromParent();
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
			CurrentWidget->AddToViewport(0);
			break;
		}
	case EGameState::Settings:
		{
			CurrentWidget->RemoveFromParent();
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), SettingsWidgetClass);
			CurrentWidget->AddToViewport(0);
			break;
		}
	case EGameState::GameOver:
		{
			ModalWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), GameOverWidgetClass);
			ModalWidget->AddToViewport(0);
			break;
		}
	default:
		{
			CurrentWidget->RemoveFromParent();
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), GameWidgetClass);
			CurrentWidget->AddToViewport(0);
			break;
		}
	}
}


