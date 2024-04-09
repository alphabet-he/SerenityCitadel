// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SerenityCitadelCharacter.h"
#include "MyGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALMODULE_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	FDateTime Date{
		2077, // year
		4, // month
		17 // day
	};

public:

	void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	FDateTime GetDate() { return Date; }

	UFUNCTION(BlueprintCallable)
	void AddDate() 
	{
		FTimespan OneDay(1, 0, 0, 0); // 1 day, 0 hours, 0 minutes, 0 seconds
		Date = Date + OneDay;
		return;
	}

	UFUNCTION(BlueprintCallable)
	void SetDate(FDateTime newDate) {
		Date = newDate;
		return;
	}

	AActor* RobotInRepair = nullptr;

	// in the future, if multiple robots, make this a list
	bool bRobotFixed = false;

	APlayerControllerTest* PlayerController = nullptr;

	ASerenityCitadelCharacter* PlayerCharacter = nullptr;

	TMap<FName, ASerenityCitadelCharacter*> MicroRobotList;

	TSubclassOf<UUserWidget> FarmingWidgetClass = nullptr;

	UUserWidget* FarmingWidget = nullptr;

	void SwitchToFarmLevel(FName levelName);

	void SwitchToHome();
};
