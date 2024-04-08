// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ComputerDesktop.h"
#include "CommissionPage.h"
#include "InTransitWidget.h"
#include "PlayerCharacter.h"
#include "DialogueWidget.h"
#include "ControlPanelWidget.h"
#include "HomeGameMode.generated.h"

/**
 * 
 */

class UCommissionButton;
class AMinimapPawn;
class ARobotMinimap;
class ARobotToRepair;
class AMinimapController;
class UMyGameInstanceSubsystem;

UCLASS()
class HOMEMODULE_API AHomeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void StartPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UComputerDesktop> DesktopWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCommissionPage> CommissionPageWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInTransitWidget> InTransitWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UControlPanelWidget> ControlPanelWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMinimapPawn> MinimapPawnClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASerenityCitadelCharacter> MicroRobotCharacterClass;

	UPROPERTY(EditAnywhere)
	FVector RobotSpawnPos;

	UPROPERTY(EditAnywhere)
	FVector MicroRobotSpawnPosInFarm;

	UComputerDesktop* DesktopWidget;
	UCommissionPage* CommissionPageWidget;
	UInTransitWidget* InTransitWidget;
	UDialogueWidget* DialogueWidget;
	UControlPanelWidget* ControlPanelWidget;

	APlayerControllerTest* GetPlayerController() { return PlayerController; }
	APlayerCharacter* GetPlayerCharacter() { return PlayerCharacter; }
	UMyGameInstanceSubsystem* GetMyGameInstanceSubsystem() {
		return MyGameInstanceSubsystem;
	}

	FName GetCurrFarmLevelName() { return LevelToLoad; }


private:
	APlayerControllerTest* PlayerController;
	APlayerCharacter* PlayerCharacter;

	AMinimapPawn* minimapPawn;
	ARobotMinimap* minimap;
	ARobotToRepair* robotInRepair;

	FName LevelToLoad;

	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

public:
	void CommissionSpawn(UCommissionButton* commissionButton);

	void SpawnMinimapPawn();

	void DestroyMinimapPawn();

	AMinimapPawn* GetMinimapPawn() {
		return minimapPawn;
	}

};
