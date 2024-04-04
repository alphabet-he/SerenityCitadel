// Fill out your copyright notice in the Description page of Project Settings.


#include "CommissionPage.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HomeGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "CommissionButton.h"
#include "RobotToRepair.h"
#include "MyGameInstanceSubsystem.h"

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
		AcceptButton->SetVisibility(ESlateVisibility::Hidden);
		RejectButton->SetVisibility(ESlateVisibility::Hidden);
		currRobotClass = nullptr;
	}
	else {
		CarlyCommissionDetail->SetVisibility(ESlateVisibility::Visible);
		BlockButton->SetVisibility(ESlateVisibility::Visible);
		AcceptButton->SetVisibility(ESlateVisibility::Visible);
		RejectButton->SetVisibility(ESlateVisibility::Visible);
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

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ARobotToRepair* RobotInRepair = GetWorld()->SpawnActor<ARobotToRepair>(
			currRobotClass, HomeGameMode->RobotSpawnPos, FRotator(90.0f, 0, 0), SpawnParameters);

		GameInstanceSubsystem->RobotInRepair = RobotInRepair;

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

void UCommissionPage::SetCurrRobotClass(TSubclassOf<ARobotToRepair> robotClass)
{
	if (currRobotClass != robotClass) {
		currRobotClass = robotClass;
	}
	else {
		currRobotClass = nullptr;
	}
	
}
