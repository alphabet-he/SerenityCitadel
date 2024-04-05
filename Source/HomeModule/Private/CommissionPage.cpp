// Fill out your copyright notice in the Description page of Project Settings.


#include "CommissionPage.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "CommissionButton.h"
#include "RobotToRepair.h"
#include "MyGameInstanceSubsystem.h"
#include "RobotMinimap.h"

void UCommissionPage::NativeConstruct()
{
	Super::NativeConstruct();

	CarlyCommissionButton->OnClicked.AddUniqueDynamic(this, &UCommissionPage::ClickCommissionDetail);
	AcceptButton->OnClicked.AddUniqueDynamic(this, &UCommissionPage::AcceptCommission);

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	PlayerController = HomeGameMode->GetPlayerController();

	PlayerCharacter = HomeGameMode->GetPlayerCharacter();

	GameInstanceSubsystem = Cast<UMyGameInstanceSubsystem>(
		GetWorld()->GetGameInstance()->GetSubsystem<UMyGameInstanceSubsystem>()
	);
	check(GameInstanceSubsystem);
}

void UCommissionPage::ClickCommissionDetail()
{
	if (CarlyCommissionDetail->GetVisibility() == ESlateVisibility::Visible) {
		CarlyCommissionDetail->SetVisibility(ESlateVisibility::Hidden);
		BlockButton->SetVisibility(ESlateVisibility::Hidden);

		if (bDealt) {
			CompleteButton->SetVisibility(ESlateVisibility::Hidden);
			WithdrawButton->SetVisibility(ESlateVisibility::Hidden);
			AcceptedStatus->SetVisibility(ESlateVisibility::Hidden);
		}
		else {
			AcceptButton->SetVisibility(ESlateVisibility::Hidden);
			RejectButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else {
		CarlyCommissionDetail->SetVisibility(ESlateVisibility::Visible);
		BlockButton->SetVisibility(ESlateVisibility::Visible);

		if (bDealt) {
			CompleteButton->SetVisibility(ESlateVisibility::Visible);
			WithdrawButton->SetVisibility(ESlateVisibility::Visible);
			AcceptedStatus->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			AcceptButton->SetVisibility(ESlateVisibility::Visible);
			RejectButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCommissionPage::AcceptCommission()
{
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}

	if (HomeGameMode->InTransitWidget) {
		HomeGameMode->InTransitWidget->AddToViewport();

		HomeGameMode->DesktopWidget->RemoveFromParent();
		PlayerCharacter->RemoveWidget(HomeGameMode->DesktopWidget);

		this->RemoveFromParent();
		PlayerCharacter->RemoveWidget(this);

		HomeGameMode->CommissionSpawn(currCommissionButton);

		// switch buttons
		AcceptButton->SetVisibility(ESlateVisibility::Hidden);
		RejectButton->SetVisibility(ESlateVisibility::Hidden);
		CompleteButton->SetVisibility(ESlateVisibility::Visible);
		WithdrawButton->SetVisibility(ESlateVisibility::Visible);
		AcceptedStatus->SetVisibility(ESlateVisibility::Visible);
		bDealt = true;

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &UCommissionPage::CommissionAcceptedEnd, 2.0f);
	}
}

void UCommissionPage::CommissionAcceptedEnd()
{
	HomeGameMode->InTransitWidget->RemoveFromParent();

	PlayerController->DisableMouseCursor();
	PlayerController->EnableMovement();

	PlayerCharacter->ShowEToInteract();
}

void UCommissionPage::SetCurrCommissionButton(UCommissionButton* commissionButton)
{
	if (currCommissionButton != commissionButton) {
		currCommissionButton = commissionButton;
	}
	else {
		currCommissionButton = nullptr;
	}
	
}
