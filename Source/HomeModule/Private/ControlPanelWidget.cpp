// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPanelWidget.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>

void UControlPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ZoomInButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickZoomInButton);
	DispatchButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickDispatchButton);
	RecallButton->OnClicked.AddUniqueDynamic(this, &UControlPanelWidget::ClickRecallButton);

	HomeGameMode = Cast<AHomeGameMode>(UGameplayStatics::GetGameMode(this));
	check(HomeGameMode);

	PlayerController = HomeGameMode->GetPlayerController();

	PlayerCharacter = HomeGameMode->GetPlayerCharacter();
}

void UControlPanelWidget::ClickZoomInButton()
{

}

void UControlPanelWidget::ClickDispatchButton()
{
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
