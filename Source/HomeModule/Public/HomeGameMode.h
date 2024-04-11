// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeWidgetManager.h"
#include "PlayerCharacter.h"
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
class AMainRobot;

UCLASS()
class HOMEMODULE_API AHomeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void StartPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHomeWidgetManager> HomeWidgetManagerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMinimapPawn> MinimapPawnClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASerenityCitadelCharacter> MicroRobotCharacterClass;

	UPROPERTY(EditAnywhere)
	FVector RobotPosOnTable;

	UPROPERTY(EditAnywhere)
	FVector RobotPosStand;

	UPROPERTY(EditAnywhere)
	FVector MicroRobotSpawnPosInFarm;

	UHomeWidgetManager* HomeWidgetManager;

	APlayerControllerTest* GetPlayerController() { return PlayerController; }
	APlayerCharacter* GetPlayerCharacter() { return PlayerCharacter; }
	UMyGameInstanceSubsystem* GetMyGameInstanceSubsystem() {
		return MyGameInstanceSubsystem;
	}

	FName GetCurrFarmLevelName() { return LevelToLoad; }

	AMainRobot* GetMainRobot() {
		return MainRobot;
	}


private:
	APlayerControllerTest* PlayerController;
	APlayerCharacter* PlayerCharacter;

	AMinimapPawn* minimapPawn;
	ARobotMinimap* minimap;
	ARobotToRepair* robotInRepair;

	FName LevelToLoad;

	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

	AMainRobot* MainRobot = nullptr;

public:
	void CommissionSpawn(UCommissionButton* commissionButton);

	void SpawnMinimapPawn();

	void DestroyMinimapPawn();

	AMinimapPawn* GetMinimapPawn() {
		return minimapPawn;
	}

	void OnRobotFixed();

};
