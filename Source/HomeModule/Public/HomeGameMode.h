// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeGameMode.generated.h"

/**
 * 
 */

class UComputerDesktop;
class UCommissionPage;

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

	UComputerDesktop* DesktopWidget;
	UCommissionPage* CommissionPageWidget;
	
};
