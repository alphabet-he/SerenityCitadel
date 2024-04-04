// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>

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

	PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);

	PlayerCharacter = PlayerController->GetPlayerCharacter();
	check(PlayerCharacter);
}
