// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "GridButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGridButtonClickDelegate, int32, Row, int32, Column);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

class UOperatingWidget;

UCLASS()
class FARMMODULE_API UGridButton : public UButton
{
	GENERATED_BODY()

public:
	int32 Row;
	int32 Column;

private:
	UOperatingWidget* widgetInstance;

private:
	UGridButton();

	UPROPERTY()
	FGridButtonClickDelegate click;

	//UPROPERTY()
	//FClickDelegate click;

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void ClickFunction(int32 Row, int32 Column);


};
