// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NinjaCharacter.h"
#include "Blueprint/UserWidget.h"
#include "PlayerControllerTest.h"
#include "SerenityCitadelCharacter.generated.h"

// Forward declaration
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class IInteractionInterface;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType)
enum class ECharacterType : uint8 {
	Count = 4 UMETA(DisplayName = "Count for the enum class"),
	BASE = 0 UMETA(DisplayName = "BASE"), 
	PLAYER = 1     UMETA(DisplayName = "PLAYER"),
	FARMER = 2	UMETA(DisplayName = "FARMER"),
	SOLDIER = 3	UMETA(DisplayName = "SOLDIER")
};

UCLASS(config = Game)
class GLOBALMODULE_API ASerenityCitadelCharacter : public ANinjaCharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ASerenityCitadelCharacter(const FObjectInitializer& ObjectInitializer);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleMove(const FInputActionValue& Value);
	virtual void HandleLook(const FInputActionValue& Value);
	virtual void HandleJump();
	virtual void HandleCrouch();
	virtual void HandleInteract();
	virtual void HandleEsc();

	// farm actions, defined in AFarmingRobotCharacter
	virtual void HandleExitFarm();
	virtual void HandleSwitchProp();

	void AddActiveWdiget(UUserWidget* widget) { ActiveWidgets.Push(widget); }
	TArray<UUserWidget*> GetActiveWidgets() { return ActiveWidgets; }
	UUserWidget* GetWidgetOnTop() { return ActiveWidgets.Top(); }
	void ClearAllWidgets() { ActiveWidgets.Empty(); }
	void RemoveWidget(UUserWidget* widget) { ActiveWidgets.Remove(widget); }

	void SetPlayerController(APlayerControllerTest* pc) { PlayerController = pc; }
	APlayerControllerTest* GetPlayerController() { return PlayerController; }

	void PauseGame();

	void ShowEToInteract();

	ECharacterType CharacterType = ECharacterType::BASE;

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere)
	float CheckInteractionBoxFreq = 0.04f;

	IInteractionInterface* InteractionInterface = nullptr;

	TArray<UUserWidget*> ActiveWidgets;

	APlayerControllerTest* PlayerController;



protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Call every CheckInteractionBoxFreq seconds
	void CheckInteractionBox();

};
