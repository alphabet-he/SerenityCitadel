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

	if (!HomeGameMode->ControlPanelWidget) {
		return;
	}

	if (PlayerCharacter->GetActiveWidgets().Contains(HomeGameMode->ControlPanelWidget)) {

		HomeGameMode->ControlPanelWidget->RemoveFromParent();
		PlayerCharacter->RemoveWidget(HomeGameMode->ControlPanelWidget);
		PlayerController->DisableMouseCursor();
		PlayerController->EnableMovementAndAction();

		EToInteractWidget->SetVisibility(true);

		PlayerCharacter->SetControllingMinimapPawn(false);
	}

	else {

		HomeGameMode->ControlPanelWidget->AddToViewport();
		PlayerCharacter->AddActiveWdiget(HomeGameMode->ControlPanelWidget);
		PlayerController->EnableMouseCursor();
		PlayerController->DisableMovementAndAction();

		EToInteractWidget->SetVisibility(false);

		if (HomeGameMode->GetMinimapPawn()) {
			PlayerCharacter->SetControllingMinimapPawn(true);
			PlayerController->EnableMovement();
		}

	}
}
