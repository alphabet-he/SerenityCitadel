// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "RobotMinimap.h"
#include "MinimapPawn.h"
#include "CommissionButton.h"
#include "RobotToRepair.h"

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

	PlayerCharacter = PlayerController->GetPlayerCharacter();
	check(PlayerCharacter);
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
