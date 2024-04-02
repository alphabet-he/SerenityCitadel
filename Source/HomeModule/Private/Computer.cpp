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

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = PlayerController->GetPlayerCharacter();
	check(PlayerCharacter);
	
	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);
}

void AComputer::InteractWithPlayer()
{
	if (!HomeGameMode->DesktopWidget) {
		UE_LOG(LogTemp, Warning, TEXT("No desktop widget instance"));
		return;
	}

	// there is widget showing
	if (PlayerCharacter->GetActiveWidgets().Contains(HomeGameMode->DesktopWidget)) 
	{
		HomeGameMode->DesktopWidget->RemoveFromParent();
		PlayerCharacter->RemoveWidget(HomeGameMode->DesktopWidget);

		// if commission widget is showing
		if (HomeGameMode->CommissionPageWidget &&
			PlayerCharacter->GetActiveWidgets().Contains(HomeGameMode->CommissionPageWidget)) {
			HomeGameMode->CommissionPageWidget->RemoveFromParent();
			PlayerCharacter->RemoveWidget(HomeGameMode->CommissionPageWidget);
		}

		PlayerController->DisableMouseCursor();
		PlayerController->EnableMovement();

		EToInteractWidget->SetVisibility(true);

	}

	else 
	{
		HomeGameMode->DesktopWidget->AddToViewport();
			
		PlayerCharacter->AddActiveWdiget(HomeGameMode->DesktopWidget);

		PlayerController->EnableMouseCursor();
		PlayerController->DisableMovement();

		EToInteractWidget->SetVisibility(false);
		
	}
	
}

