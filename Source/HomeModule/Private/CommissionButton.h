// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include <RobotToRepair.h>
#include <RobotMinimap.h>
#include "CommissionButton.generated.h"


/**
 * 
 */
UCLASS()
class UCommissionButton : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARobotToRepair> RobotClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARobotMinimap> RobotMinimapClass;

private:
	UCommissionButton();

	UFUNCTION()
	void OnClick();

	AHomeGameMode* HomeGameMode;
	
};
