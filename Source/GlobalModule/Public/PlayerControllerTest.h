// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerTest.generated.h"


//Forward declarations
class UEnhancedInputComponent;
class ASerenityCitadelCharacter;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * 
 */
UCLASS()
class GLOBALMODULE_API APlayerControllerTest : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Movement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Movement")
	UInputAction* ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Interaction")
	UInputAction* ActionInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Movement Mapping")
	UInputMappingContext* MovementMappingContent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Interaction Mapping")
	UInputMappingContext* InteractionMappingContent = nullptr;

public:
	UFUNCTION()
	void DisableMovement();

	UFUNCTION()
	void EnableMovement();

	UFUNCTION()
	void EnableMouseCursor();

	UFUNCTION()
	void DisableMouseCursor();

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	ASerenityCitadelCharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = nullptr;
};
