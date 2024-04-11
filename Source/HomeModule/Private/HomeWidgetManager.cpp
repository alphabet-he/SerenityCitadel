// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeWidgetManager.h"
#include <Kismet\GameplayStatics.h>
#include "PlayerControllerTest.h"
#include "PlayerCharacter.h"

void UHomeWidgetManager::HandleEsc()
{
	if (!PlayerController) {
		PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		check(PlayerController);
	}

	if (!PlayerCharacter) {
		PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPlayerCharacter());
		check(PlayerCharacter);
	}

	check(PlayerCharacter);
	check(PlayerController);

	// showing commission page
	if (ManagerSwitcher->GetActiveWidgetIndex() == 1) {
		ShowDesktop();
	}

	else if (ManagerSwitcher->GetActiveWidgetIndex() != 0){

		// is control panel
		if (ManagerSwitcher->GetActiveWidgetIndex() == 4) {
			PlayerCharacter->SetControllingMinimapPawn(false);
		}

		HideAllWidgets();
		PlayerController->EnableMovementAndAction();
		PlayerController->DisableMouseCursor();
		PlayerCharacter->ShowEToInteract();
	}
}
