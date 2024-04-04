// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
};
