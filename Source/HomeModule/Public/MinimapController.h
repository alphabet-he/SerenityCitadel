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
class AMinimapPawn;
class UInputMappingContext;

UCLASS()
class HOMEMODULE_API AMinimapController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Movement Mapping")
	UInputMappingContext* MovementMappingContent = nullptr;

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

	UFUNCTION()
	void HandleMove(const FInputActionValue& Value);

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = nullptr;

	UPROPERTY()
	AMinimapPawn* MinimapPawn;


};
