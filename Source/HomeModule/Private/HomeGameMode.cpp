// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "RobotMinimap.h"
#include "MinimapPawn.h"
#include "CommissionButton.h"
#include "RobotToRepair.h"
#include "MinimapController.h"

void AHomeGameMode::StartPlay()
{
	Super::StartPlay();

	DesktopWidget = CreateWidget<UComputerDesktop>(GetWorld(), DesktopWidgetClass);
	DesktopWidget->RemoveFromParent();

	CommissionPageWidget = CreateWidget<UCommissionPage>(GetWorld(), CommissionPageWidgetClass);
	CommissionPageWidget->RemoveFromParent();

	InTransitWidget = CreateWidget<UInTransitWidget>(GetWorld(), InTransitWidgetClass);
	InTransitWidget->RemoveFromParent();

	DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
	DialogueWidget->RemoveFromParent();

	ControlPanelWidget = CreateWidget<UControlPanelWidget>(GetWorld(), ControlPanelWidgetClass);
	ControlPanelWidget->RemoveFromParent();

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPlayerCharacter());
	check(PlayerCharacter);

	//MinimapController = GetWorld()->SpawnActor<AMinimapController>(MinimapControllerClass);
}

void AHomeGameMode::SpawnMinimapPawn()
{
	if (!minimap) return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector spawnLoc = minimap->GetPawnSpawnPos();

	minimapPawn = GetWorld()->SpawnActor<AMinimapPawn>(
		MinimapPawnClass, minimap->GetPawnSpawnPos(), FRotator(0), SpawnParameters);
	if (minimapPawn) {
		minimapPawn->SetForwardDirection(minimap->GetForwardDirection());
		minimapPawn->SetRightDirection(minimap->GetRightDirection());
		
		PlayerCharacter->SetControllingMinimapPawn(true);
		PlayerCharacter->SetControlledMinimapPawn(minimapPawn);
	}
	
	


}

void AHomeGameMode::CommissionSpawn(UCommissionButton* commissionButton)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	robotInRepair = GetWorld()->SpawnActor<ARobotToRepair>(
		commissionButton->RobotClass, RobotSpawnPos, FRotator(90.0f, 0, 0), SpawnParameters);

	minimap = GetWorld()->SpawnActor<ARobotMinimap>(
		commissionButton->RobotMinimapClass, FVector(1000.0f, 1000.0f, -3000.0f), FRotator(0), SpawnParameters);
}

void AHomeGameMode::DestroyMinimapPawn()
{
	if (minimapPawn) {
		minimapPawn->K2_DestroyActor();
		minimapPawn = nullptr;
	}
	PlayerCharacter->SetControllingMinimapPawn(false);
	PlayerCharacter->SetControlledMinimapPawn(nullptr);
}
