// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/MobileGamePlayerController.h"
#include "GameElement.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

AMobileGamePlayerController::AMobileGamePlayerController()
{
	bShowMouseCursor = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableTouchOverEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

//TODO:: Make existing camera MainCamera instead of spawn camera
void AMobileGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	MainCamera = GetWorld()->SpawnActor<ACameraActor>();
	
	if (!MainCamera)
	{
		return;
	}
	
	MainCamera->SetActorRotation(FRotator(-90.f, 0.f, 0.f));
	MainCamera->SetActorLocation(FVector(0.f, 0.f, 500.f));
	SetViewTarget(MainCamera);
		
	UCameraComponent* MainCameraComponent = MainCamera->GetCameraComponent();
	MainCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	MainCameraComponent->OrthoWidth = 1536.f;
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
