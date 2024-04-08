// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerenityCitadelCharacter.h"
#include "FarmingRobotCharacter.generated.h"

/**
 * 
 */
class UMyGameInstanceSubsystem;

UENUM(BlueprintType)
enum class EFarmingState : uint8 {
	Count = 5 UMETA(DisplayName = "Count for the enum class"),
	IDLE = 0 UMETA(DisplayName = "IDLE"),
	DIGGING = 1     UMETA(DisplayName = "DIG"),
	WATERING = 2	UMETA(DisplayName = "WATER"),
	DECONTAMINATING = 3	UMETA(DisplayName = "DECONTAMINATE"),
	SEEDING = 4	UMETA(DisplayName = "SEED")
};

UCLASS()
class FARMMODULE_API AFarmingRobotCharacter : public ASerenityCitadelCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFarmingRobotCharacter(const FObjectInitializer& ObjectInitializer);

	void HandleExitFarm() override;
	void HandleSwitchProp() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<EFarmingState> AvailableStates;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

	EFarmingState CurrFarmingState = EFarmingState::IDLE;

private:
	void BeginPlay() override;

	void UpdateState();

	
};
