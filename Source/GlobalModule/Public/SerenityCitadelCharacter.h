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

UCLASS(config = Game)
class GLOBALMODULE_API ASerenityCitadelCharacter : public ANinjaCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	ASerenityCitadelCharacter(const FObjectInitializer& ObjectInitializer);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleJump();
	void HandleCrouch();
	void HandleInteract();
	void HandleEsc();

	void AddActiveWdiget(UUserWidget* widget) { ActiveWidgets.Push(widget); }
	TArray<UUserWidget*> GetActiveWidgets() { return ActiveWidgets; }
	UUserWidget* GetWidgetOnTop() { return ActiveWidgets.Top(); }
	void ClearAllWidgets() { ActiveWidgets.Empty(); }
	void RemoveWidget(UUserWidget* widget) { ActiveWidgets.Remove(widget); }

	void SetPlayerController(APlayerControllerTest* pc) { PlayerController = pc; }
	APlayerControllerTest* GetPlayerController() { return PlayerController; }

	void PauseGame();

	void ShowEToInteract();

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere)
	float CheckInteractionBoxFreq = 0.04f;

	IInteractionInterface* InteractionInterface = nullptr;

	TArray<UUserWidget*> ActiveWidgets;

	APlayerControllerTest* PlayerController;

private:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Call every CheckInteractionBoxFreq seconds
	void CheckInteractionBox();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
