// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInteractable.h"
#include "ControlPanel.generated.h"

/**
 * 
 */
class APlayerControllerTest;
class ASerenityCitadelCharacter;
class AHomeGameMode;

UCLASS()
class AControlPanel : public ACommonInteractable
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	APlayerControllerTest* PlayerController;

	ASerenityCitadelCharacter* PlayerCharacter;

	AHomeGameMode* HomeGameMode;

private:
	virtual void InteractWithPlayer() override;
};
