// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileGamePlayerController.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

AMobileGamePlayerController::AMobileGamePlayerController()
{
	bShowMouseCursor = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableTouchOverEvents = true;
	bEnableMouseOverEvents = true;
	bForceFeedbackEnabled = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

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
