// Fill out your copyright notice in the Description page of Project Settings.


#include "Computer.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerControllerTest.h"
#include "HomeGameMode.h"
#include "ComputerDesktop.h"
#include "CommissionPage.h"
#include "SerenityCitadelCharacter.h"

// Sets default values
AComputer::AComputer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AComputer::BeginPlay()
{
	Super::BeginPlay();
	
	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	// seems like this begin play is called before game mode's start play,
	// so the player character and controller cannot be initialized
	PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	PlayerController = HomeGameMode->GetPlayerController();
}

void AComputer::InteractWithPlayer()
{
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}

	// there is widget showing
	if (!EToInteractWidget->IsVisible())
	{
		HomeGameMode->HomeWidgetManager->HideAllWidgets();

		PlayerController->DisableMouseCursor();
		PlayerController->EnableMovementAndAction();

		EToInteractWidget->SetVisibility(true);

	}

	else 
	{
		HomeGameMode->HomeWidgetManager->ShowDesktop();

		PlayerController->EnableMouseCursor();
		PlayerController->DisableMovementAndAction();

		EToInteractWidget->SetVisibility(false);
		
	}
	
}

