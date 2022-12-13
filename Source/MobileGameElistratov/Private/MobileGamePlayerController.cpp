// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/MobileGamePlayerController.h"
#include "MobileGameElistratov/Public/GameElement.h"

AMobileGamePlayerController::AMobileGamePlayerController()
{
	bShowMouseCursor = true;
	bEnableTouchEvents = bEnableClickEvents = true;
	bEnableTouchOverEvents = bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMobileGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobileGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobileGamePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMobileGamePlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMobileGamePlayerController::OnTouchReleased);

}

void AMobileGamePlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);

	if (AGameElement* GameElement = Cast<AGameElement>(Hit.GetActor()))
	{
		GameElement->TouchResponse();
	}
}

void AMobileGamePlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;
}

void AMobileGamePlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void AMobileGamePlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

