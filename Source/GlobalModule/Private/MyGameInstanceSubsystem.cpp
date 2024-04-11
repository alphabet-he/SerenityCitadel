// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceSubsystem.h"
#include <Kismet/GameplayStatics.h>

void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMyGameInstanceSubsystem::SwitchToFarmLevel(FName levelName)
{
	if (!PlayerController) {
		PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}

	if (MicroRobotList.Contains(levelName)) {
		PlayerController->UnPossess();
		PlayerController->Possess(MicroRobotList[levelName]);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Micro robot not spawned"));
	}

	if (HomeWidgetManager) {
		HomeWidgetManager->RemoveFromParent();
	}

	if (FarmingWidget) {
		FarmingWidget->AddToViewport();
	}
	
}

void UMyGameInstanceSubsystem::SwitchToHome()
{
	if (!bStartFromHome) {
		UE_LOG(LogTemp, Warning, TEXT("Didn't start from home"));
		return;
	}

	if (!PlayerController) {
		PlayerController = Cast<APlayerControllerTest>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}

	if (PlayerCharacter) {
		PlayerController->UnPossess();
		PlayerController->Possess(PlayerCharacter);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Cannot find home player character"));
	}

	if (FarmingWidget) {
		FarmingWidget->RemoveFromParent();
	}

	if (HomeWidgetManager) {
		HomeWidgetManager->AddToViewport();
	}
	
}
