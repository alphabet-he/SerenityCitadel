// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerenityCitadelCharacter.h"
#include "FarmingRobotCharacter.generated.h"

/**
 * 
 */
class UMyGameInstanceSubsystem;
class APlant;
class ACommonFarmManager;
class UWidgetComponent;

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
	void HandleAnalyze() override;

	TSubclassOf<APlant> GetHoldingSeed() {
		return HoldingSeed;
	}

public:
	UPROPERTY(EditAnywhere)
	TArray<EFarmingState> AvailableStates;

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<APlant>, int> SeedPackage;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* TargetWidget;

	UPROPERTY(EditAnywhere)
	float WaterAddMoisture = 0.05f;

	UPROPERTY(EditAnywhere)
	float DecontaminateMinusPollution = 0.3f;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UMyGameInstanceSubsystem* MyGameInstanceSubsystem;

	EFarmingState CurrFarmingState = EFarmingState::IDLE;

	TSubclassOf<APlant> HoldingSeed = nullptr;

	ACommonFarmManager* FarmManager = nullptr;

private:
	void BeginPlay() override;

	void UpdateState();

	void HandleInteract() override;



	
};
