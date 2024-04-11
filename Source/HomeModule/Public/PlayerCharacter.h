// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerenityCitadelCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class AMinimapPawn;
class UHomeWidgetManager;

UCLASS()
class HOMEMODULE_API APlayerCharacter : public ASerenityCitadelCharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	void HandleMove(const FInputActionValue& Value) override;
	void HandleEsc() override;

	void SetControlledMinimapPawn(AMinimapPawn* p) {
		ControlledMinimapPawn = p;
	}

	void SetControllingMinimapPawn(bool controlling) {
		ControllingMinimapPawn = controlling;
	}

	void SetHomeWidgetManager(UHomeWidgetManager* manager) {
		HomeWidgetManager = manager;
	}

private:
	AMinimapPawn* ControlledMinimapPawn;
	bool ControllingMinimapPawn = false;

	UHomeWidgetManager* HomeWidgetManager;
};
