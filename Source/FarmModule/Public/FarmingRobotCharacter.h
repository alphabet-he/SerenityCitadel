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
	DIG = 1     UMETA(DisplayName = "DIG"),
	WATER = 2	UMETA(DisplayName = "WATER"),
	DECONTAMINATE = 3	UMETA(DisplayName = "DECONTAMINATE"),
	SEED = 4	UMETA(DisplayName = "SEED")
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

	void SetFarmManager(ACommonFarmManager* farmManager) {
		FarmManager = farmManager;
	}

	float currBattery = 1;
	float currWater = 1;
	float currPurifyGas = 1;

public:
	UPROPERTY(EditAnywhere)
	UWidgetComponent* TargetWidget;

	UPROPERTY(EditAnywhere)
	TArray<EFarmingState> AvailableStates;

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<APlant>, int> SeedPackage;

	UPROPERTY(EditAnywhere)
	float WaterAddMoisture = 0.05f;

	UPROPERTY(EditAnywhere)
	float DecontaminateMinusPollution = 0.3f;

	// Battery Usage
	UPROPERTY(EditAnywhere)
	float DigUseBattery = 0.03f;

	UPROPERTY(EditAnywhere)
	float WaterUseBattery = 0.01f;

	UPROPERTY(EditAnywhere)
	float DecontaminateUseBattery = 0.05f;

	UPROPERTY(EditAnywhere)
	float SeedUseBattery = 0.02f;

	UPROPERTY(EditAnywhere)
	float AnalyzeUseBattery = 0.01f;

	// Resource Usage
	UPROPERTY(EditAnywhere)
	float WaterOnceUsage = 0.125f;

	UPROPERTY(EditAnywhere)
	float PurifyOnceUsage = 0.15f;

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
