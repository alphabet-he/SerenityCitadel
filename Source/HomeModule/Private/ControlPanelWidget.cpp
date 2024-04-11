// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPanelWidget.h"
#include <Kismet/GameplayStatics.h>
#include "MyGameInstanceSubsystem.h"
#include "HomeGameMode.h"
#include <Components/Image.h>

void UControlPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ZoomInButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickZoomInButton);
	DispatchButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickDispatchButton);
	RecallButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickRecallButton);

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);
}

void UControlPanelWidget::ClickZoomInButton()
{
	HomeGameMode->HomeWidgetManager->HideAllWidgets();

	PlayerController->DisableMouseCursor();
	PlayerController->EnableMovementAndAction();

	PlayerCharacter->ShowEToInteract();

	PlayerCharacter->SetControllingMinimapPawn(false);

	HomeGameMode->GetMyGameInstanceSubsystem()->SwitchToFarmLevel(HomeGameMode->GetCurrFarmLevelName());
	
}

void UControlPanelWidget::ClickDispatchButton()
{
	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}
	
	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	RecallButton->SetIsEnabled(true);
	DispatchButton->SetIsEnabled(false);

	HomeGameMode->SpawnMinimapPawn();

	PlayerController->EnableMovement();
}

void UControlPanelWidget::ClickRecallButton()
{
	HomeGameMode->DestroyMinimapPawn();

	RecallButton->SetIsEnabled(false);
	DispatchButton->SetIsEnabled(true);
	ZoomInButton->SetIsEnabled(false);

	PlayerController->DisableMovement();
	
}

void UControlPanelWidget::ClickPowerOnButton()
{
	if (!PlayerController) {
		PlayerController = HomeGameMode->GetPlayerController();
	}

	if (!PlayerCharacter) {
		PlayerCharacter = HomeGameMode->GetPlayerCharacter();
	}

	PlayerController->DisableMouseCursor();
	if (HomeGameMode->GetMyGameInstanceSubsystem()->bRobotFixed) {
		Succeeded->SetVisibility(ESlateVisibility::Visible);
		PowerOnButton->SetIsEnabled(false);
	}

	if (HomeGameMode->GetMyGameInstanceSubsystem()->bRobotFixed) {
		Failed->SetVisibility(ESlateVisibility::Visible);
		PowerOnButton->SetIsEnabled(false);
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &UControlPanelWidget::HideFailedNotice, 1.5f);
		PlayerController->DisableInteraction();
		PlayerController->DisableUIActions();
	}

}

void UControlPanelWidget::HideFailedNotice()
{
	Failed->SetVisibility(ESlateVisibility::Hidden);
	PlayerController->EnableMouseCursor();
	PowerOnButton->SetIsEnabled(true);
	PlayerController->EnableInteraction();
	PlayerController->EnableUIActions();
}
