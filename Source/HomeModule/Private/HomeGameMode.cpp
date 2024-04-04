// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGameMode.h"
#include "ComputerDesktop.h"
#include "CommissionPage.h"

void AHomeGameMode::StartPlay()
{
	Super::StartPlay();

	DesktopWidget = CreateWidget<UComputerDesktop>(GetWorld(), DesktopWidgetClass);
	DesktopWidget->RemoveFromParent();

	CommissionPageWidget = CreateWidget<UCommissionPage>(GetWorld(), CommissionPageWidgetClass);
	CommissionPageWidget->RemoveFromParent();
}
