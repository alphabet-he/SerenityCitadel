// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MinimapController.generated.h"

/**
 * 
 */

class UInputAction;
class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class HOMEMODULE_API AMinimapController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	UInputAction* ActionMove = nullptr;

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = nullptr;
};
