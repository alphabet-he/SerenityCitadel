// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include <FarmModuleEnums.h>
#include "GridOperationButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOperationButtonClickDelegate, int32, row, int32, col, EGridType, type);

class UOperatingWidget;
class UFarmingSubsystem;

UCLASS()
class FARMMODULE_API UGridOperationButton : public UButton
{
	GENERATED_BODY()

public:
	int32 Row;
	int32 Column;
	EGridType _GridType;
	GridOperation Operation;

private:
	UOperatingWidget* widgetInstance;
	UFarmingSubsystem* subsystem;

private:
	UGridOperationButton();

	UPROPERTY()
	FOperationButtonClickDelegate click;

	//UPROPERTY()
	//FClickDelegate click;

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void ClickFunction(int32 row, int32 col, EGridType type);

	
};
