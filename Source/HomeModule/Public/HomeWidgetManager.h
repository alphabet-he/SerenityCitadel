// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "ComputerDesktop.h"
#include "CommissionPage.h"
#include "InTransitWidget.h"
#include "DialogueWidget.h"
#include "ControlPanelWidget.h"
#include "HomeWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class HOMEMODULE_API UHomeWidgetManager : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* ManagerSwitcher;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* EmptyWidget;

	UPROPERTY(meta = (BindWidget))
	UComputerDesktop* DesktopWidget;

	UPROPERTY(meta = (BindWidget))
	UCommissionPage* CommissionPageWidget;

	UPROPERTY(meta = (BindWidget))
	UInTransitWidget* InTransitWidget;

	UPROPERTY(meta = (BindWidget))
	UDialogueWidget* DialogueWidget;

	UPROPERTY(meta = (BindWidget))
	UControlPanelWidget* ControlPanelWidget;

public:
	void HideAllWidgets() {
		ManagerSwitcher->SetActiveWidgetIndex(0);
	}

	void ShowDesktop() {
		ManagerSwitcher->SetActiveWidgetIndex(1);
	}

	void ShowCommissionPage() {
		ManagerSwitcher->SetActiveWidgetIndex(2);
	}

	void ShowInTransit() {
		ManagerSwitcher->SetActiveWidgetIndex(3);
	}

	void ShowControlPanel() {
		ManagerSwitcher->SetActiveWidgetIndex(4);
	}

	void ShowDialogue() {
		ManagerSwitcher->SetActiveWidgetIndex(5);
	}

	void HandleEsc();


private:
	APlayerCharacter* PlayerCharacter;

	APlayerControllerTest* PlayerController;
};
