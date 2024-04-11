// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components\WidgetSwitcher.h>
#include "GlobalWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALMODULE_API UGlobalWidgetManager : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* GlobalSwitcher;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* EmptyWidget;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* HomeLevelWidget;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* FarmLevelWidget;

public:
	UUserWidget* GetHomeLevelWidget() {
		return HomeLevelWidget;
	}

	UUserWidget* GetFarmLevelWidget() {
		return FarmLevelWidget;
	}

	void HideAllWidgets() {
		GlobalSwitcher->SetActiveWidgetIndex(0);
	}

	void ShowHomeLevelWidget() {
		GlobalSwitcher->SetActiveWidgetIndex(1);
	}

	void ShowFarmLevelWidget() {
		GlobalSwitcher->SetActiveWidgetIndex(2);
	}
	
};
