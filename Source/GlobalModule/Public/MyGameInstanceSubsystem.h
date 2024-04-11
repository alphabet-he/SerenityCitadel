// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SerenityCitadelCharacter.h"
#include "GlobalWidgetManager.h"
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

	// whether start from home game mode
	bool bStartFromHome = false;

	APlayerControllerTest* PlayerController = nullptr;

	ASerenityCitadelCharacter* PlayerCharacter = nullptr;

	TMap<FName, ASerenityCitadelCharacter*> MicroRobotList;

	TSubclassOf<UUserWidget> FarmingWidgetClass = nullptr;

	UGlobalWidgetManager* GlobalWidgetManager;

	UUserWidget* FarmingWidget = nullptr;

	UUserWidget* HomeWidgetManager = nullptr;

	void SwitchToFarmLevel(FName levelName);

	void SwitchToHome();

	UUserWidget* CreateFarmingWidget() {
		FarmingWidget = CreateWidget<UUserWidget>(GetWorld(), FarmingWidgetClass);
		return FarmingWidget;
	};

	UFUNCTION(BlueprintCallable)
	void InitializeGlobalWidgetManager(TSubclassOf<UGlobalWidgetManager> managerClass);
};
