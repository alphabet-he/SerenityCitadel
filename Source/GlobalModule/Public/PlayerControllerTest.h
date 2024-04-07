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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Action")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Action")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Action")
	UInputAction* ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|Character Interaction")
	UInputAction* ActionInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Action|UI Actions")
	UInputAction* ActionUIEsc = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Movement Mapping")
	UInputMappingContext* MovementMappingContent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Action Mapping")
	UInputMappingContext* ActionMappingContent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|Interaction Mapping")
	UInputMappingContext* InteractionMappingContent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Mapping|UI Actions Mapping")
	UInputMappingContext* UIActionMappingContent = nullptr;

public:
	UFUNCTION()
	void DisableMovementAndAction();

	UFUNCTION()
	void EnableMovementAndAction();

	UFUNCTION()
	void DisableMovement();

	UFUNCTION()
	void EnableMovement();

	UFUNCTION()
	void DisableAction();

	UFUNCTION()
	void EnableAction();

	UFUNCTION()
	void EnableMouseCursor();

	UFUNCTION()
	void DisableMouseCursor();

	UFUNCTION()
	ASerenityCitadelCharacter* GetPlayerCharacter() 
	{
		return PlayerCharacter;
	};

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
