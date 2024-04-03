// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ComputerDesktop.h"
#include "CommissionPage.h"
#include "InTransitWidget.h"
#include "SerenityCitadelCharacter.h"
#include "DialogueWidget.h"
#include "HomeGameMode.generated.h"

/**
 * 
 */


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
	FVector RobotSpawnPos;

	UComputerDesktop* DesktopWidget;
	UCommissionPage* CommissionPageWidget;
	UInTransitWidget* InTransitWidget;
	UDialogueWidget* DialogueWidget;

	APlayerControllerTest* GetPlayerController() { return PlayerController; }
	ASerenityCitadelCharacter* GetPlayerCharacter() { return PlayerCharacter; }

private:
	APlayerControllerTest* PlayerController;
	ASerenityCitadelCharacter* PlayerCharacter;
};
