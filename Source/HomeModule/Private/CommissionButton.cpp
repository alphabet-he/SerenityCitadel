// Fill out your copyright notice in the Description page of Project Settings.


#include "CommissionButton.h"
#include <Kismet/GameplayStatics.h>
#include "HomeGameMode.h"

UCommissionButton::UCommissionButton()
{
	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));

	OnClicked.AddDynamic(this, &UCommissionButton::OnClick);
}

void UCommissionButton::OnClick()
{
	if (!HomeGameMode) {
		HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	}

	HomeGameMode->HomeWidgetManager->CommissionPageWidget->SetCurrCommissionButton(this);
}
