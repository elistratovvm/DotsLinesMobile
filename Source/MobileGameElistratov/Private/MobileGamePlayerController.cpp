// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/MobileGamePlayerController.h"
#include "GameElement.h"

AMobileGamePlayerController::AMobileGamePlayerController()
{
	bShowMouseCursor = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableTouchOverEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMobileGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMobileGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction(
		"SetDestination",
		IE_Pressed,
		this,
		&AMobileGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction(
		"SetDestination",
		IE_Released,
		this,
		&AMobileGamePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(
		IE_Pressed,
		this,
		&AMobileGamePlayerController::OnTouchPressed);
	InputComponent->BindTouch(
		IE_Released,
		this,
		&AMobileGamePlayerController::OnTouchReleased);

}

void AMobileGamePlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);

	//Debug method, delete after development will be completed
	//------------------------------------------------------------------------------------------------------------------
	//TODO:: think about #if WITH_EDITOR or other macroses for remove code in release
	if (Hit.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Actor: %s"), *Hit.GetActor()->GetName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Green,
			TEXT("No Actors in hit"));
	}
	//------------------------------------------------------------------------------------------------------------------
	
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
