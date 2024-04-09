// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <EnhancedInputComponent.h>
#include "SerenityCitadelCharacter.h"
#include <EnhancedInputSubsystems.h>

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Bind farming related actions
	if (PlayerCharacter->CharacterType == ECharacterType::FARMER) {
		// Bind action mapping context
		checkf(FarmingMappingContent, TEXT("FarmingMappingContent is not defined"));
		InputSubsystem->AddMappingContext(FarmingMappingContent, 0);

		// Bind actions
		if (ActionExitFarm)
			EnhancedInputComponent->BindAction(ActionExitFarm, ETriggerEvent::Triggered, PlayerCharacter,
				&ASerenityCitadelCharacter::HandleExitFarm);

		if (ActionSwitchProp)
			EnhancedInputComponent->BindAction(ActionSwitchProp, ETriggerEvent::Triggered, PlayerCharacter,
				&ASerenityCitadelCharacter::HandleSwitchProp);

		if (ActionAnalyze)
			EnhancedInputComponent->BindAction(ActionAnalyze, ETriggerEvent::Triggered, PlayerCharacter,
				&ASerenityCitadelCharacter::HandleAnalyze);
	}
}

void AMyPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
