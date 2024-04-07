// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "MinimapPawn.h"

void AMinimapController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);


	// Define player character
	MinimapPawn = Cast<AMinimapPawn>(aPawn);
	checkf(MinimapPawn, TEXT("Casting to MinimapPawn failed."));

	// Define Enhanced input component
	if (aPawn->InputComponent) {
		EnhancedInputComponent = Cast<UEnhancedInputComponent>(aPawn->InputComponent);
	}

	checkf(EnhancedInputComponent, TEXT("Cannot access Enhanced Input Component"));

	// Get local player subsystem
	if (GetGameInstance()->GetFirstLocalPlayerController()) {
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			GetGameInstance()->GetFirstLocalPlayerController()->GetLocalPlayer());
		
	}
	checkf(InputSubsystem, TEXT("Cannot access input local subsystem."));

	// Clear exsiting mappings
	InputSubsystem->ClearAllMappings();

	// Bind movement mapping context
	checkf(MovementMappingContent, TEXT("MovementMappingContext is not defined"));
	InputSubsystem->AddMappingContext(MovementMappingContent, 0);

	// Bind actions
	if (ActionMove)
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, 
			&AMinimapController::HandleMove);
}

void AMinimapController::OnUnPossess()
{
	InputSubsystem->ClearAllMappings();
	Super::OnUnPossess();
}

void AMinimapController::HandleMove(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("HERE.........."));
	MinimapPawn->HandleMove(Value);
}
