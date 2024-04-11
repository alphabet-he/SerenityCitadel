// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPanel.h"
#include <Kismet/GameplayStatics.h>
#include "HomeGameMode.h"

void AControlPanel::BeginPlay()
{
	Super::BeginPlay();

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);
}

void AControlPanel::InteractWithPlayer()
{
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}

	if (!EToInteractWidget->IsVisible()) {

		HomeGameMode->HomeWidgetManager->HideAllWidgets();
		PlayerController->DisableMouseCursor();
		PlayerController->EnableMovementAndAction();

		EToInteractWidget->SetVisibility(true);

		PlayerCharacter->SetControllingMinimapPawn(false);
	}

	else {

		HomeGameMode->HomeWidgetManager->ShowControlPanel();
		PlayerController->EnableMouseCursor();
		PlayerController->DisableMovementAndAction();

		EToInteractWidget->SetVisibility(false);

		if (HomeGameMode->GetMinimapPawn()) {
			PlayerCharacter->SetControllingMinimapPawn(true);
			PlayerController->EnableMovement();
		}

	}
}
