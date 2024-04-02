// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerTest.h"
#include <EnhancedInputComponent.h>
#include "SerenityCitadelCharacter.h"
#include <EnhancedInputSubsystems.h>


void APlayerControllerTest::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Define player character
	PlayerCharacter = Cast<ASerenityCitadelCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("Casting to SerenityCitadelCharacter failed."));

	// Set controller information for the character
	PlayerCharacter->SetPlayerController(this);

	// Define Enhanced input component
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Cannot access Enhanced Input Component"));

	// Get local player subsystem
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Cannot access input local subsystem."));
	
	// Clear exsiting mappings
	InputSubsystem->ClearAllMappings();

	// Bind interaction mapping context
	checkf(InteractionMappingContent, TEXT("InteractionMappingContext is not defined"));
	InputSubsystem->AddMappingContext(InteractionMappingContent, 0);

	// Bind movement mapping context
	checkf(MovementMappingContent, TEXT("MovementMappingContext is not defined"));
	InputSubsystem->AddMappingContext(MovementMappingContent, 0);

	// Bind UI mapping context
	checkf(UIActionMappingContent, TEXT("UIMappingContext is not defined"));
	InputSubsystem->AddMappingContext(UIActionMappingContent, 0);

	


	// Bind actions
	if (ActionMove)
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleMove);

	if (ActionLook)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleLook);

	if (ActionJump)
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleJump);

	if (ActionCrouch)
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleCrouch);

	if (ActionInteract)
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleInteract);

	if (ActionUIEsc)
		EnhancedInputComponent->BindAction(ActionUIEsc, ETriggerEvent::Triggered, PlayerCharacter,
			&ASerenityCitadelCharacter::HandleEsc);

}

void APlayerControllerTest::OnUnPossess()
{
	InputSubsystem->ClearAllMappings();
	Super::OnUnPossess();
}

void APlayerControllerTest::DisableMovement()
{
	InputSubsystem->RemoveMappingContext(MovementMappingContent);
}

void APlayerControllerTest::EnableMovement()
{
	InputSubsystem->AddMappingContext(MovementMappingContent, 0);
}

void APlayerControllerTest::EnableMouseCursor()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void APlayerControllerTest::DisableMouseCursor()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;

}
